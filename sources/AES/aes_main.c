#include "aes.h"
#include <stdint.h>
#include <stdio.h>
#include <woody.h>

int AES_file(char *file, char *key, int mode)
{
	int file_id;
	file_id = 1;
	if (strlen(key) != 32){
		printf("Error: Key must be 64 characters long\n");
		return(-1);
	}
	if (mode == 1)
	{
		int tmp_fd = open(file, O_RDONLY);
		int crashtest_fd = open("encoded", O_RDONLY | O_WRONLY | O_CREAT | O_TRUNC, 0777);
		t_binary_reader *reader_tmp = new_binary_reader(tmp_fd);
		if (!reader_tmp)
		{
			printf("Error: Cannot read file %s\n", file);
			return (1);
		}
		uint8_t tm[17];
		size_t round = 0;
		while (round * 16 < 16)
		{
			for (int i = 0; i < 16; i++)
			{
				tm[i] = reader_tmp->get_uint8(reader_tmp);
				printf("%03i ", tm[i]);
			}
			printf("\n");
			tm[16] = 0;
			char *tmp = calloc(1, 256);
			BytesToString(tm, tmp);
			printf("before : %s\n", tmp);
			uint8_t **encoded = AES_encrypt(tmp, key);
			if (encoded == NULL)
			{
				printf("error\n");
				return (0);
			}
			char str1[32];
			for (int i = 0; i < 16; i++)
			{
				dprintf(crashtest_fd, "%c", (* encoded)[i]);
				printf("%03i ", (* encoded)[i]);
			}
			round++;

			//this work
			int tmp_fd2 = open("encoded", O_RDONLY);
			t_binary_reader *reader_tmp2 = new_binary_reader(tmp_fd2);
			int crashtest_fd2 = open("decoded", O_RDONLY | O_WRONLY | O_CREAT | O_TRUNC, 0777);
			printf("\ndecoded\n");
			for (int i = 0; i < 16; i++)
			{
				tm[i] = reader_tmp2->get_uint8(reader_tmp2);
				printf("%03i ", tm[i]);
			}
			tm[17] = 0;
			printf("\n");
			BytesToString(tm, tmp);
			uint8_t **decoded = AES_decrypt(tmp, key);
			// stringToBytes(decoded, tmp, 32);
			for (int i = 0; i < 16; i++)
			{	
				// dprintf(crashtest_fd2, "%c", (*decoded)[i]);
				printf("%03i ", (*decoded)[i]);
			}
			printf("\n");
		}
	}
	else if (mode == 2)
	{
		file_id = 2;
		int tmp_fd = open("encoded", O_RDONLY);
		int crashtest_fd = open("decoded", O_RDONLY | O_WRONLY | O_CREAT | O_TRUNC, 0777);
		t_binary_reader *reader_tmp = new_binary_reader(tmp_fd);
		if (!reader_tmp)
		{
			printf("Error: Cannot read file %s\n", file);
			return (1);
		}
	}
}
