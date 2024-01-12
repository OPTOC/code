#include <zip2.h>
#include <iostream>
static int verbose = 0;

int
minitar(int argc, const char **argv)
{
	const char *filename = NULL;
	int compress, flags, mode, opt;

	(void)argc;
	mode = 'x';
	verbose = 0;
	compress = '\0';
	flags = ARCHIVE_EXTRACT_TIME;

	/* Among other sins, getopt(3) pulls in printf(3). */
	while (*++argv != NULL && **argv == '-') { //这里只是获取-参数
		const char *p = *argv + 1;

		while ((opt = *p++) != '\0') {
			switch (opt) {
#ifndef NO_CREATE
			case 'c':
				mode = opt;
				break;
#endif
			case 'f':
				if (*p != '\0')
					filename = p;
				else
					filename = *++argv; //获取压缩包名称
				p += strlen(p);
				break;
#ifndef NO_BZIP2_CREATE
			case 'j':
				compress = opt;
				break;
#endif
			case 'p':
				flags |= ARCHIVE_EXTRACT_PERM;
				flags |= ARCHIVE_EXTRACT_ACL;
				flags |= ARCHIVE_EXTRACT_FFLAGS;
				break;
			case 't':
				mode = opt;
				break;
			case 'v':
				verbose++;
				break;
			case 'x':
				mode = opt;
				break;
#ifndef NO_BZIP2_CREATE
			case 'y':
				compress = opt;
				break;
#endif
#ifndef NO_COMPRESS_CREATE
			case 'Z':
				compress = opt;
				break;
#endif
#ifndef NO_GZIP_CREATE
			case 'z':
				compress = opt;
				break;
#endif
			default:
				usage();
			}
		}
	}

	switch (mode) {
#ifndef NO_CREATE
	case 'c':
		create(filename, compress, argv);
		break;
#endif
	case 't':
		extract(filename, 0, flags);
		break;
	case 'x':
		extract(filename, 1, flags);
		break;
	}

	return (0);
}


#ifndef NO_CREATE
static char buff[16384];

static void
create(const char *filename, int compress, const char **argv)
{
	struct archive *a;
	struct archive_entry *entry;
	ssize_t len;
	int fd;

	a = archive_write_new();
	switch (compress) {
#ifndef NO_BZIP2_CREATE
	case 'j': case 'y':
		archive_write_add_filter_bzip2(a);
		break;
#endif
#ifndef NO_COMPRESS_CREATE
	case 'Z':
		archive_write_add_filter_compress(a);
		break;
#endif
#ifndef NO_GZIP_CREATE
	case 'z':
		archive_write_add_filter_gzip(a);
		break;
#endif
	default:
		archive_write_add_filter_none(a);
		break;
	}
	archive_write_set_format_ustar(a);
	if (filename != NULL && strcmp(filename, "-") == 0)
		filename = NULL;
	archive_write_open_filename(a, filename);

	while (*argv != NULL) {
		struct archive *disk = archive_read_disk_new();
#ifndef NO_LOOKUP
		archive_read_disk_set_standard_lookup(disk);
#endif
		int r;
        std::string file_Path = std::string(*argv);
        size_t lastSlashPos = file_Path.find_last_of('/');
        std::string directory = file_Path.substr(lastSlashPos);
		std::string directory1 = file_Path.substr(0,lastSlashPos);
        
		r = archive_read_disk_open(disk, *argv);//打开文件
        // printf("argc里面的东西:%s\n",*argv );
		if (r != ARCHIVE_OK) {
			errmsg(archive_error_string(disk));//打印错误信息
			errmsg("\n");
			exit(1);
		}

		for (;;) {
			int needcr = 0;

			entry = archive_entry_new();
			r = archive_read_next_header2(disk, entry);
			if (r == ARCHIVE_EOF)
				break;
			if (r != ARCHIVE_OK) {
				errmsg(archive_error_string(disk));
				errmsg("\n");
				exit(1);
			}
			archive_read_disk_descend(disk);
			if (verbose) {
				msg("a ");
				msg(archive_entry_pathname(entry));
				needcr = 1;
			}

			//用来设置相对路径   也就是设置压缩包打开后只有thread
			archive_entry_set_pathname(entry, archive_entry_pathname(entry) + directory1.length() + 1);

			r = archive_write_header(a, entry);
			if (r < ARCHIVE_OK) {
				errmsg(": ");
				errmsg(archive_error_string(a));
				needcr = 1;
			}
			if (r == ARCHIVE_FATAL)
				exit(1);
			if (r > ARCHIVE_FAILED) {
#if 0
				/* Ideally, we would be able to use
				 * the same code to copy a body from
				 * an archive_read_disk to an
				 * archive_write that we use for
				 * copying data from an archive_read
				 * to an archive_write_disk.
				 * Unfortunately, this doesn't quite
				 * work yet. */
				copy_data(disk, a);
#else
				/* For now, we use a simpler loop to copy data
				 * into the target archive. */
				fd = open(archive_entry_sourcepath(entry), O_RDONLY);
				len = read(fd, buff, sizeof(buff));
				while (len > 0) {
					archive_write_data(a, buff, len);
					len = read(fd, buff, sizeof(buff));
				}
				close(fd);
#endif
			}
			archive_entry_free(entry);
			if (needcr)
				msg("\n");
		}
		archive_read_close(disk);
		archive_read_free(disk);
		argv++;
	}
	archive_write_close(a);
	archive_write_free(a);
}
#endif

static void
extract(const char *filename, int do_extract, int flags)
{
	struct archive *a;
	struct archive *ext;
	struct archive_entry *entry;
	int r;

	a = archive_read_new();
	ext = archive_write_disk_new();
	archive_write_disk_set_options(ext, flags);
#ifndef NO_BZIP2_EXTRACT
	archive_read_support_filter_bzip2(a);
#endif
#ifndef NO_GZIP_EXTRACT
	archive_read_support_filter_gzip(a);
#endif
#ifndef NO_COMPRESS_EXTRACT
	archive_read_support_filter_compress(a);
#endif
#ifndef NO_TAR_EXTRACT
	archive_read_support_format_tar(a);
#endif
#ifndef NO_CPIO_EXTRACT
	archive_read_support_format_cpio(a);
#endif
#ifndef NO_LOOKUP
	archive_write_disk_set_standard_lookup(ext);
#endif
	if (filename != NULL && strcmp(filename, "-") == 0)
		filename = NULL;
	if ((r = archive_read_open_filename(a, filename, 10240))) {
		errmsg(archive_error_string(a));
		errmsg("\n");
		exit(r);
	}
	for (;;) {
		int needcr = 0;
		r = archive_read_next_header(a, &entry);
		if (r == ARCHIVE_EOF)
			break;
		if (r != ARCHIVE_OK) {
			errmsg(archive_error_string(a));
			errmsg("\n");
			exit(1);
		}
		if (verbose && do_extract)
			msg("x ");
		if (verbose || !do_extract) {
			msg(archive_entry_pathname(entry));
			msg(" ");
			needcr = 1;
		}
		if (do_extract) {
			r = archive_write_header(ext, entry);
			if (r != ARCHIVE_OK) {
				errmsg(archive_error_string(a));
				needcr = 1;
			}
			else {
				r = copy_data(a, ext);
				if (r != ARCHIVE_OK)
					needcr = 1;
			}
		}
		if (needcr)
			msg("\n");
	}
	archive_read_close(a);
	archive_read_free(a);

	archive_write_close(ext);
  	archive_write_free(ext);
	exit(0);
}

static int
copy_data(struct archive *ar, struct archive *aw)
{
	int r;
	const void *buff;
	size_t size;
	int64_t offset;

	for (;;) {
		r = archive_read_data_block(ar, &buff, &size, &offset);
		if (r == ARCHIVE_EOF)
			return (ARCHIVE_OK);
		if (r != ARCHIVE_OK) {
			errmsg(archive_error_string(ar));
			return (r);
		}
		r = archive_write_data_block(aw, buff, size, offset);
		if (r != ARCHIVE_OK) {
			errmsg(archive_error_string(ar));
			return (r);
		}
	}
}

static void
msg(const char *m)
{
	write(1, m, strlen(m));
}

static void
errmsg(const char *m)
{
	if (m == NULL) {
		m = "Error: No error description provided.\n";
	}
	write(2, m, strlen(m));
}

static void
usage(void)
{
/* Many program options depend on compile options. */
	const char *m = "Usage: minitar [-"
#ifndef NO_CREATE
	    "c"
#endif
#ifndef	NO_BZIP2
	    "j"
#endif
	    "tvx"
#ifndef NO_BZIP2
	    "y"
#endif
#ifndef NO_COMPRESS
	    "Z"
#endif
#ifndef NO_GZIP
	    "z"
#endif
	    "] [-f file] [file]\n";

	errmsg(m);
	exit(1);
}
// int main(int argc, const char **argv)
// {	
// 	//压缩
//     const char *chis[] = { 
//         "./zip2",
//         "-czf",
//         "thread.tar",
//         "/home/zjh/thread",
//         NULL  // 参数数组的末尾必须为NULL
//     };
// 	// //解压
//     // const char *chis[] = { 
//     //     "./zip2",
//     //     "-xf",
//     //     "thread.tar",
//     //     NULL  // 参数数组的末尾必须为NULL
//     // };
//     minitar(sizeof(chis), chis);
// }