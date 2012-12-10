#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>

int list_dir(char *path)
{
	DIR *dir;
	struct stat stat_buf;
	struct dirent *dirent;
	char dest_path[100];
	struct passwd *user;
	struct group *group;
	unsigned long file_size;
	struct tm *t;
	char *file_name;
	unsigned long modenum;
	char mode[11] = {0};

	dir = opendir(path);
	while ((dirent = readdir(dir))) {
		if (dirent->d_name[0] == '.')
			continue;

		memset(dest_path, 0, 100);
		strcpy(dest_path, path);
		strcat(dest_path, "/");
		strcat(dest_path, dirent->d_name);
		stat(dest_path, &stat_buf);	

		switch(stat_buf.st_mode & S_IFMT) {
			case S_IFBLK:
				mode[0] = 'b';
				break;
			case S_IFCHR:
				mode[0] = 'c';
				break;
			case S_IFDIR:
				mode[0] = 'd';
				break;
			case S_IFIFO:
				mode[0] = 'f';
				break;
			case S_IFLNK:
				mode[0] = 's';
				break;
			case S_IFREG:
				mode[0] = 'r';
				break;
			default:
				mode[0] = '-';
				break;
		}

		modenum = (unsigned long)stat_buf.st_mode;
		mode[1] = (modenum & S_IRUSR ? 'r' : '-');
		mode[2] = (modenum & S_IWUSR ? 'w' : '-');
		mode[3] = (modenum & S_IXUSR ? 'x' : '-');
		mode[4] = (modenum & S_IRGRP ? 'r' : '-');
		mode[5] = (modenum & S_IWGRP ? 'w' : '-');
		mode[6] = (modenum & S_IXGRP ? 'x' : '-');
		mode[7] = (modenum & S_IROTH ? 'r' : '-');
		mode[8] = (modenum & S_IWOTH ? 'w' : '-');
		mode[9] = (modenum & S_IXOTH ? 'x' : '-');

		user = getpwuid(stat_buf.st_uid);
		group = getgrgid(stat_buf.st_gid);
		file_size = (unsigned long)stat_buf.st_size;
		t = localtime(&stat_buf.st_ctime);
		file_name = dirent->d_name;
		
		printf("%s  ", mode);
		printf("%s  ", user->pw_name);
		printf("%s  ", group->gr_name);
		printf("%10lu  ", file_size);
		printf("%2d-%2d %2d:%2d  "
				, t->tm_mon + 1
				, t->tm_mday
				, t->tm_hour
				, t->tm_min);
		printf("%s\n", file_name);
	}
	
	closedir(dir);

	return 0;
}

int main(int argc, char *argv[])
{
	char *path;

	if (argc < 2)
	{
		path = "./";
		list_dir(path);

		return 0;
	}

	int i = 1;
//	while (argv[i][0]) {
//		if (argv[i][0] == '-') {
//			switch (argv[i][1]) {
//				case 'l':
//
//					break;
//				case 'a':
//
//					break;
//			}
//		}
//	}

	while (i < argc) {
		printf("%s :\n", argv[i]);
		path = argv[i];
		list_dir(path);
		i++;
	}

	return 0;
}
