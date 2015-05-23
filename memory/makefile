run:	mmap_demo fileio_1char fileio_file
		cp alphabet vowels_mmap
		mmap_demo vowels_mmap
		cat alphabet
		cat vowels_mmap
		cp alphabet vowels_1char
		fileio_1char vowels_1char
		cat vowels_1char
		cp alphabet vowels_file
		fileio_file vowels_file
		cat vowels_file

% : %.c
		gc $@

.PHONY: x
x:
		rm -f vowels_mmap mmap_demo \
			  vowels_1char fileio_1char \
			  vowels_file fileio_file \
			  mmap_example1 mmap_example2
