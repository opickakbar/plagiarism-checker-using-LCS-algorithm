#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <algorithm>
#include<process.h>

//char file1[100];
//char file2[100];
int jumlahline1 = 0;
int maxkolom1=0;
char **data1 = NULL;

int jumlahline2 = 0;
int maxkolom2=0;
char **data2 = NULL;

char *matrix1 = NULL;
char *matrix2 = NULL;
int penampung1 = 0, penampung2 = 0;

void readFile1()
{
	jumlahline1 = 0;
	maxkolom1 = 0;
	int maxstring = 0;
	char read[1000];
	
	FILE *read1 = fopen("file1.txt", "r");
	if(read1 != NULL)
	{
		while(!feof(read1))
		{
			fscanf(read1, "%[^\n]\n", read);
			jumlahline1++;
			
			//hitung total string
			maxstring += strlen(read);
			
			//cek jumlah kolom di file
			maxkolom1 = std::max(maxstring,maxkolom1);
		}
	}
	else
	{
		printf("Failed file1");
	}
	
	fclose(read1);
	
	//char array dinamis nampung data file(line+kolom)
	data1 = new char *[jumlahline1];
	
	for(int i = 0;i < jumlahline1;i++)
	{
		data1[i] = new char[maxkolom1];
	}
	
	int idx = 0;
	FILE *baca = fopen("file1.txt", "r");
	if(baca != NULL)
	{
		while(!feof(baca))
		{
			fscanf(baca, "%[^\n]\n", data1[idx]);
			idx++;
		}
	}
	else
	{
		printf("Failed to read file1");
	}
	
	fclose(baca);

}

void readFile2()
{
	jumlahline2 = 0;
	maxkolom2 = 0;
	int maxstring = 0;
	char read[1000];

	FILE *read2 = fopen("file2.txt", "r");
	if(read2 != NULL)
	{
		while(!feof(read2))
		{
			fscanf(read2, "%[^\n]\n", read);
			jumlahline2++;		
			maxstring += strlen(read);
			//cek panjang kolom di file
			maxkolom2 = std::max(maxstring,maxkolom2);
		}
	}
	else
	{
		printf("Failed to read file2");
	}
	
	fclose(read2);

	//char array dinamis,nampung data file(line+kolom)
	data2 = new char *[jumlahline2];
	for(int i = 0;i < jumlahline2;i++)
	{
		data2[i] = new char[maxkolom2];
	}
	int idx = 0;
	FILE *baca = fopen("file2.txt", "r");
	if(baca != NULL)
	{
		while(!feof(baca))
		{
			fscanf(baca, "%[^\n]\n", data2[idx]);
			idx++;
		}
	}
	else
	{
		printf("Failed to read file2");
	}
	
	fclose(baca);

}

void lcs(char *kata1, char *kata2)
{
	int matrix[100][100];
	float jumlah = 0;
	float pers = 0;
	//bikin map
	for (int i=0; i<=strlen(kata1); i++)
	{
		for (int j=0; j<=strlen(kata2); j++)
		{
			//kasih dipinggir nilai 0
			if (i == 0 || j == 0)
				matrix[i][j] = 0;
			//kalau sama,kasih nilai 1+nilai pojok sebelah kiri
			else if (kata1[i-1] == kata2[j-1])
				matrix[i][j] = matrix[i-1][j-1] + 1;

			//kalau beda kasi nilai yg terbesar (atas/kiri)
			else
			{
				matrix[i][j] = std::max(matrix[i-1][j], matrix[i][j-1]);
			}
		}
	}

	//mulai dari index yg paling akhir
	int index = matrix[strlen(kata1)][strlen(kata2)];
	char lcs[100];

	lcs[index] = '\0';
	
	int i = strlen(kata1), j = strlen(kata2);
	//logic lcs
	while (i > 0 && j > 0)
	{
	//masukin ke lcs nya (kalau karakter sama)
      if (kata1[i-1] == kata2[j-1])
	  {
		  jumlah+=1;
          lcs[index-1] = kata1[i-1];
          i--;
		  j--;
		  index--; 
      }
	  //kalau gak, bandingin mana yg lebih besar(atas atau kiri)), lalu pindahin keatas
      else if (matrix[i-1][j] > matrix[i][j-1]) i--;
	  //atau kekiri
      else j--;
   }

	if(strlen(lcs) == 0)
	{
		strcpy(lcs, "Tidak ada yg sama");
	}

	if(strlen(kata1) > strlen(kata2))
		pers = (jumlah/strlen(kata1))*100;
	else if(strlen(kata2) > strlen(kata1))
		pers = (jumlah/strlen(kata2))*100;
	else
		pers = jumlah/strlen(kata1)*100;

	char pri = '%';
	printf("===========================================================================\n");
	printf("\nString 1 = %s\n\nString 2 = %s\n\n\nLCS nya = %s\n\n", kata1, kata2, lcs);
	printf("Persentase kemiripan = %.1f%c", pers, pri);

}
 

void banding()
{
	float jumlah = 0;
	float pers = 0;
	//hitungpanjang baris+kolom file
	for(int i = 0; i < jumlahline1;i++)
	{
		penampung1 += strlen(data1[i]);
		penampung1++;
	}
	for(int i = 0; i < jumlahline2;i++)
	{
		penampung2 += strlen(data2[i]);
		penampung2++;
	}

	//masukin ke matrix1 semua data di file1
	int indexhelp = 0;
	matrix1 = new char [penampung1];
	for(int i=0;i<jumlahline1;i++)
	{
		for(int y=0;y<strlen(data1[i]);y++)
		{
			matrix1[indexhelp] = data1[i][y];
			indexhelp++;
		}
		matrix1[indexhelp] = '\n';
		indexhelp++;
	}
	//masukin ke matrix2 semua data di file2
	indexhelp = 0;
	matrix2 = new char [penampung2];
	for(int i=0;i<jumlahline2;i++)
	{
		for(int y=0;y<strlen(data2[i]);y++)
		{
			matrix2[indexhelp] = data2[i][y];
			indexhelp++;
		}
		matrix2[indexhelp] = '\n';
		indexhelp++;
	}
	/*int p1, p2;
	p1 = strlen(file1);
	p2 = strlen(file2);*/

	//int matrix[100][100];

	//matrix utk map (dinamis array)
	int **matrix = new int *[penampung1+1];
	for(int i = 0;i < penampung1+1;i++)
	{
		matrix[i] = new int[penampung2];
	}

	//matrix[0][0] = 0;
	//map lcs
	for(int i = 0; i <= penampung1; i++)
	{
		for(int j = 0; j <= penampung2; j++)
		{
			//kasih yg dipinggir 0
			if(i == 0||j==0)
			{
			 matrix[i][j] = 0;
			}
			//kalau sama kasih 1+nilai di pojok kiri atasnya
			else if(matrix1[i-1] == matrix2[j-1])
			{
				matrix[i][j] = 1+matrix[i-1][j-1];
			}
			//kalau beda, ambil nilai terbesar (kiri atau atas)
			else
			{
				matrix[i][j] = std::max(matrix[i-1][j], matrix[i][j-1]);
			}
		}
	}
	//mulai dari index yg terakhir
	int idx = matrix[penampung1][penampung2];
	//variabel lcs dinamis
	char *lcs = new char[std::max(penampung1,penampung2)];
	lcs[idx]= '\0';
	//logic lcs
	while(penampung1 > 0 && penampung2 > 0)
	{
		//masukin ke lcs kalau sama
		if(matrix1[penampung1-1] == matrix2[penampung2-1])
		{
			lcs[idx-1] = matrix1[penampung1-1];
			jumlah+=1;
			penampung1--;
			penampung2--;
			idx--;
		}
		//kalau beda, (bandingin atas & kiri), pindahin ke atas
		else if(matrix[penampung1-1][penampung2] > matrix[penampung1][penampung2-1])
		{
			penampung1--;
		}
		//atau kiri
		else
		{
			penampung2--;
		}
	}

	if(strlen(lcs) == 0)
	{
		strcpy(lcs, "Tidak ada yg sama");
	}

	if(penampung1 > penampung2)
		pers = (jumlah/strlen(matrix1))*100;
	else if(penampung2 > penampung1)
		pers = (jumlah/strlen(matrix2))*100;
	else
		pers = (jumlah/strlen(matrix1))*100;

	char pri = '%';
	//printf("\nData file 1 = %s\nData file 2 = %s\n\n\nLCS nya = %s\n\n", file1, file2, lcs);
	printf("===========================================================================\n");
	printf("\nPersentase kemiripan = %.2f %c", pers, pri);
}

void spasi()
{
	for(int i = 0; i < 25; i++)
	{
		printf("\n");
	}
}

int main()
{
	int input;
	char kata1[100];
	char kata2[100];
	readFile1();
	readFile2();

	do
	{
		spasi();
		printf("Compare string/file using LCS algorithm\n");
		printf("=======================================\n");
		printf("1. Compare 2 string\n");
		printf("2. Compare 2 file\n");
		printf("3. Exit\n");
		printf("Choose >> ");
		scanf("%d", &input);fflush(stdin);
		switch(input)
		{
			case 1:
				{
					spasi();
					printf("Input Kata 1 : ");
					scanf("%[^\n]", kata1); fflush(stdin);
					printf("Input Kata 2 : ");
					scanf("%[^\n]", kata2); fflush(stdin);
					spasi();
					lcs(kata1, kata2);
					printf("\n\nPress enter to continue..");
					getchar();
				break;}
			case 2:
				{
					spasi();
					banding();
					printf("\n\nPress enter to continue..");
					getchar();
				break;}
		}
	}while(input != 3);
	
	//banding();
	printf("Thanks for using this application, by [TR 16-1]^^");
	getchar();
	return 0;
}