#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])

{
        //check to make sure there is indeed one command line argument (i.e in addition to the the ./recover argument)
        if (argc != 2)
        {
            printf("Please provide one command line argument which is the address of address of the forensic image in the IDE directory\n");
            return 1;
        }

        //open the file up and store the file pointer in memory_file
        FILE *memory_file = fopen(argv[1], "r");

        if (memory_file == NULL)
        {
            printf("Not enough memory to store the memory_file1\n");
            return 1;
        }

        char filename[8];

        //This is the variable that keeps a track of the number of JPEG files that we have found so far. It increases by 1 when the computer is able to find the JPEG signature at the start of a 512 block Bytes. The increase by 1 takes place at the end of this loop.
        int x = 0;
        unsigned char BYTES[512];


    //This is the while loop which is to go on forever unless the break condition below is met (i.e. the end of file is reached).

    while (fread(BYTES, 1, 512, memory_file) == 512)
    {
        if (BYTES[0] == 0xff && BYTES[1] == 0xd8 && BYTES[2] == 0xff && (BYTES[3] & 0Xf0) == 0xe0)
        {
        //This initial condition is checking to see if we have encountered the first JPEG file. If x is indeed 0, then we have just found our first JPEG file.
        if (x == 0)
        {

            //The following code somehow changes the name of the jpg file from 000.jpg to 00x.jpg where x represents the decimal number of the image we have been able to identify so far.
            sprintf(filename, "%03i.jpg", x);

            FILE *image = fopen(filename, "a");

            if(image == NULL)
            {
            printf("Not enough memory to store the memory_file2\n");
            return 2;
            }

            //The following code is intended to take the next 512 block of BYTES from the memory_file and write it in the file pointed to by image.
            fwrite(BYTES, 1, 512, image);

            //This is the variable that keeps a track of the number of JPEG files that we have found so far. It increases by 1 only the computer is able to find the JPEG signature at the start of a 512 block Bytes. The increase by 1 takes place at the end of this loop.
            x++;

            fclose(image);

        }

        else
        {
            //The following code somehow changes the name of the jpg file from 000.jpg to 00x.jpg where x represents the decimal number of the image we have been able to identify so far.
            sprintf(filename, "%03i.jpg", x);

            FILE *image = fopen(filename, "a");

            if(image == NULL)
            {
                printf("Not enough memory to store the memory_file3\n");
                return 3;
            }

            //The following code is intended to take the next 512 block of BYTES from the memory_file and write it in the file pointed to by image.
            fwrite(BYTES, 1, 512, image);

            //This is the variable that keeps a track of the number of JPEG files that we have found so far. It increases by 1 only the computer is able to find the JPEG signature at the start of a 512 block Bytes. The increase by 1 takes place at the end of this loop.
            x++;
            fclose(image);

        }
    }

        //The following code is executed when the first four bytes don't give us a JPEG signature
        else
        {
            if(x != 0)
            {
                //The following code somehow changes the name of the jpg file from 000.jpg to 00x.jpg where x represents the decimal number of the image we have been able to identify so far.
                sprintf(filename, "%03i.jpg", (x - 1));

                FILE *image = fopen(filename, "a");

                if(image == NULL)
                {
                    printf("Not enough memory to store the memory_file3\n");
                    return 3;
                }


            //The following code is intended to take the next 512 block of BYTES from the memory_file and write it in the file pointed to by image.
                fwrite(BYTES, 1, 512, image);
                fclose(image);
            }
        }
    }
    fclose(memory_file);
    return 0;


}

