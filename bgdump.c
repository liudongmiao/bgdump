/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Tue 06 Sep 2011 11:05:22 PM CST
 * Modified : Wed 07 Sep 2011 10:42:59 PM CST
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "rtmp.h"
#include "bible.h"

#ifndef BUFSIZ
#define BUFSIZ 8192
#endif

#ifndef VERSION
#define VERSION "niv"
#endif

#ifndef AUTHOR
#define AUTHOR "mclean"
#endif

#define APP "bibles/"
#define FLASHVER "LNX 10,3,183,7"
#define SWFURL "http://www.biblegateway.com/audioplayer.swf"
#define TCURL "rtmp://stream.bgcdn.com/bibles/"
#define PAGEURL "http://www.biblegateway.com/audio/"
#define HOSTNAME "stream.bgcdn.com"

RTMP *rtmp;
char *buffer;
char *version = VERSION;
char *author = AUTHOR;

int RTMP_ParseURL(const char *url, int *protocol, AVal *host,
		unsigned int *port, AVal *playpath, AVal *app)
{
	return 0;
}

static int download(char *osis, int chapter)
{
	struct stat sb;
	int size, pipe;
	char pageurl[256];
	char playpath[256];
	char path[256];
	double duration = 0;

	RTMP_Init(rtmp);

	rtmp->Link.protocol = RTMP_PROTOCOL_RTMP;
	rtmp->Link.hostname = (AVal)AVC(HOSTNAME);
	rtmp->Link.port = 1935;
	rtmp->Link.app = (AVal)AVC(APP);
	rtmp->Link.flashVer = (AVal)AVC(FLASHVER);
	rtmp->Link.swfUrl = (AVal)AVC(SWFURL);
	rtmp->Link.tcUrl = (AVal)AVC(TCURL);
	sprintf(pageurl, PAGEURL "%s/%s/%s.%d", author, version, osis, chapter); 
	rtmp->Link.pageUrl = (AVal){pageurl, strlen(pageurl)};
	sprintf(playpath, "%s-%s/%s.%d", version, author, osis, chapter); 
	rtmp->Link.playpath = (AVal){playpath, strlen(playpath)};

	printf("downloading %s .....", playpath);
	fflush(stdout);
	sprintf(path, "%s.mp3", playpath);
	if (stat(path, &sb) == 0 && sb.st_size == 0) {
		unlink(path);
	}
	pipe = open(path, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (pipe < 0) {
		perror("open");
		return errno;
	}

	size = RTMP_Connect(rtmp, NULL);
	if (size == FALSE) {
		perror("rtmp_conect");
		return EINVAL;
	}

	do {
		size = RTMP_Read(rtmp, buffer, BUFSIZ);
		if (duration <= 0) {
			duration = RTMP_GetDuration(rtmp);
		}
		if (rtmp->m_read.status == RTMP_READ_COMPLETE) {
			size = 0;
			break;
		}
  		if (!RTMP_IsConnected(rtmp)) {
			size = -1;
			break;
		}
		if (size > 0) {
			write(pipe, buffer, size);
			if (duration > 0) {
				printf("\b\b\b\b\b%04.1f%%",
						((double)rtmp->m_read.timestamp) / (duration * 10.0));
				fflush(stdout);
			}
		}
	} while (size >= 0);
	close(pipe);
	RTMP_Close(rtmp);

	if (size != 0 && stat(path, &sb) == 0) {
		if (sb.st_size == 0) {
			unlink(path);
		} else {
			sprintf(buffer, "%s.failed", path);
			rename(path, buffer); 
		}
	}
	printf("\b\b\b\b\b%s\n", size == 0 ? "completed" : "incomplete");
	return size;
}

static int list(void)
{
	int i;
	printf("Available books:\n");
	for (i = 0; i < ARRAY_SIZE(books); i++) {
		printf("\t%s(%d): %s\n", books[i].osis, books[i].chapter, books[i].human);
	}
	printf("Available versions:\n");
	for (i = 0; i < ARRAY_SIZE(audios); i++) {
		printf("\t%s(%s): %s\n", audios[i].audio, audios[i].language, audios[i].human);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	struct stat sb;
	int opt, i;
	int chapter = 0, available = 0;
	char *book = NULL;
	char audio[256];
	
	while ((opt = getopt(argc, argv, "v:a:b:c:l")) != -1) {
		switch (opt) {
			case 'v':
				version = optarg;
				break;
			case 'a':
				author = optarg;
				break;
			case 'b':
				book = optarg;
				break;
			case 'c':
				chapter = atoi(optarg);
				break;
			case 'l':
				return list();
		} 
	}

	sprintf(audio, "%s-%s", version, author);
	for (i = 0; i < ARRAY_SIZE(audios); i++) {
		if (strcasecmp(audios[i].audio, audio) == 0) {
			available = 1;
			break;
		}
	}
	if (!available) {
		fprintf(stderr, "Invalid version `%s' or author `%s'\n", version, author);
		return EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(books); i++) {
		if (!book || strcasecmp(books[i].osis, book) == 0) {
			available = 1;
			break;
		}
	}

	if (!available) {
		fprintf(stderr, "Invalid book `%s'\n", book);
		return EINVAL;
	}

	if ((rtmp = RTMP_Alloc()) == NULL || (buffer = malloc(BUFSIZ)) == NULL) {
		perror("malloc");
		return ENOMEM;
	}

	if (stat(audio, &sb) == -1) {
		if (errno == ENOENT) {
			mkdir(audio, 0755);
		} else {
			perror("stat");
			return errno;
		}
	} else if (!S_ISDIR(sb.st_mode)) {
		fprintf(stderr, "%s is not a directory\n", audio);
		return errno;
	}

	if (book) {
		if (chapter > books[i].chapter) {
			fprintf(stderr, "Invalid chapter `%d'\n", chapter);
			return EINVAL;
		}
		if (chapter) {
			download(books[i].osis, chapter);
		} else {
			for (chapter = 1; chapter <= books[i].chapter; chapter++) {
				download(books[i].osis, chapter);
			}
		}
		
	} else {
		for (i = 0; i < ARRAY_SIZE(books); i++) {
			for (chapter = 1; chapter <= books[i].chapter; chapter++) {
				download(books[i].osis, chapter);
			}
		}
	}

	RTMP_Free(rtmp);
	free(buffer);

	return 0;
}
