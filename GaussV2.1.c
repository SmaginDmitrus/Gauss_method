#include<stdio.h>
#include<stdlib.h>
#include<conio.h> 
#include<math.h>
#include<time.h>

struct matrix
{ 
	double *matrix;
	double *free_coefficients;

};

void fill_matrix(int pull,double* mat,double* free_coefficients,int x, int y)
{
	if (pull == 1)
	{

		printf("Write matrix \n");


	for (int i = 0; i < x; i++)// ввод матрицы
	{
		for(int j = 0; j < y; j++)
		{
			scanf("%lf",&mat[i*x+j]) ;
		}
	}

	printf("Write free coefficients of system in the same order:\n");
	for (int i = 0; i < x; i++)// ввод матрицы
	{	
		scanf("%lf",&free_coefficients[i]) ;	
	}

	}else

	{

		for (int i = 0; i < x; i++)// ввод матрицы
		{
			for(int j = 0; j < y; j++)
			{
				mat[i*x+j] = rand()%10+1;
			}
		}

		printf("Write free coefficients of system in the same order:\n");
		for (int i = 0; i < x; i++)// ввод матрицы
		{	
			free_coefficients[i] = rand()%10+1 ;	
		}

	}
}

void swap (double *mat,int a,int b,int x ,int y) //в матрице mat размером x*y меняет местами строку a и b 
	{
		double k = 0;
		for (int i =0;i<y;i++)
		{
			k = mat[a*y+i];
			mat[a*y+i] = mat[b*y +i];
			mat[b*y +i]= k;
		}
	}

void subs(double *mat,int work,int rez,double term,double del) // метод, вычитающий из одной строки другую 
{
		mat[rez] = mat[rez] - ((mat[work]/del)*term);
	
}
void Gauss_check_answer(double *mat,double *free,double* answers,int x, int y)
{
	double del = 1.0;
	int flag = 0;
	
	for (int w = 0; w < x; w++)// алгоритм вычитания рабочей строки
		{
			
			if ((mat[w*y+w] < 0.000001)&&(mat[w*y+w]>-0.000001))
				{ 
					if ((free[w]<0.000001)&&(free[w]>-0.000001))
					{
						flag = 1;
					}else
					{
						flag = 2;
					}
				}
				
		}
	switch(flag)
	{
		case 0:
			for (int j =0;j<x;j++)
			{
				del = mat[j*y+j];
				answers[j] = free[j]/del;
				printf("x%d = %lf \n",j,free[j]/del);
			}
			break;
		case 1:
			printf("Infinity number of awnswers");
			break;
		case 2:
			printf("No answer");
			break;
	}
}


void Gauss(double *mat,double *free,int x,int y)
{
	
	for(int w =0;w<x-1;w++) 
	{
		double min  = mat[w*y +w]; // алгоритм выстраивания ступенчатого вида
		for (int i = 1+w;i<x;i++)
		{
			if ((min > mat[(i)*y+w])&&((mat[(i)*y +w]>0.000001)||(mat[i*y + w]<-0.000001)))
			{
				min = mat[(i)*y+w];
				swap(mat,w,i,x,y);
				swap(free,w,i,x,1); 
			}


		}

		double del = mat[w*y +w];
		for (int i = 1+w; i < x; i++)// алгоритм вычитания рабочей строки
		{
			
			double term = mat[(i)*y+w];
			if ((del > 0.000001) || (del < -0.000001))
				{
					

					for(int j = w; j < y; j++)
					{		 
						subs(mat,w*y +j,(i)*y+j,term,del); //mat[(i+1)*y+j]= mat[(i+1)*y+j] - ((mat[w*y +j]/mat[(w*y+w)]) * term  ) 			
					}

					subs(free,w,i,term,del);
				}

			for (int k = 0; k < x; k++) // вывод конечной матрицы
			{ 
				printf("\n");
				for(int j = 0; j < y; j++)
				{
					printf("%lf,\t",mat[k*x+j]);
				}
				printf("%lf",free[k]);
			}
			printf("\n"); 
		}
	}

	for (int i = 0;i<x-1;i++) // обратный ход Гаусса
	{	
		double del  = mat[(x-i)*y-1-i ];
		if ((del > 0.000001) || (del < -0.000001))
		{
			for (int j = i+1;j<x;j++)
			{
				double term = mat[(x-j)*y-1-i];
				mat[(x-j)*y-1-i] =mat[(x-j)*y-1-i] - term;
				subs(free,x-1-i,x-1-j,term,del);

			}
		}

	}

};

int main(){
	int x,y;
	int pull = 0;
	double sum = 0.0;	
	printf("write number of lines and coloumns \n");
	scanf("%d %d",&x,&y);
	srand(time(NULL));
	struct matrix mat;
	if ((mat.matrix = malloc(x*y*sizeof(double)))== NULL) 
	{
		printf("Error: can't allocate memory");
        _getch();
        exit(1);
	}
	mat.free_coefficients = (double*) malloc(x*sizeof(double));
	double *xes,*answers;
	xes = (double*) malloc(y*sizeof(double));
	answers = (double*) malloc(y*sizeof(double));


	printf("To create random matrix insert 0,to fill it yourself insert 1, to check Gauss Gass_accuracy insert 2 \n");
	scanf("%d",&pull);

	if ((pull == 1) || (pull == 0))
	{
		fill_matrix(pull,mat.matrix,mat.free_coefficients,x,y);

		
		printf("\n _______________________________________________________________________________\n ");

		

		Gauss(mat.matrix,mat.free_coefficients,x,y); // применение метода Гаусса

		
		for (int i = 0; i < x; i++) // вывод конечной матрицы
		{ 
			printf("\n");
			for(int j = 0; j < y; j++)
			{
				printf("%lf,\t",mat.matrix[i*x+j]);
			}
			printf("%lf",mat.free_coefficients[i]);
		}
		printf("\n");
		Gauss_check_answer(mat.matrix,mat.free_coefficients,answers,x,y);
	}
	else
	{
		printf("Now please insert your own answers.Matrix will be generated autimatically and you'll see dispersion of that Gauss method programm.\n");
		for (int i = 0;i<y;i++)
		{
			 scanf("%lf",&xes[i]); 
		}

		for (int i = 0; i < x; i++)// ввод матрицы
		{
			for(int j = 0; j < y; j++)
			{
				mat.matrix[i*x+j] = rand()%10+1;
			}
		}
		for (int i = 0; i < x; i++)// ввод матрицы
		{
			for(int j = 0; j < y; j++)
			{
				sum += mat.matrix[i*x+j]*xes[j];
			}
			mat.free_coefficients[i] = sum;
			sum = 0.0;
		}
		Gauss(mat.matrix,mat.free_coefficients,x,y);
		Gauss_check_answer(mat.matrix,mat.free_coefficients,answers,x,y);
		for (int i=0;i<y;i++)
		{
			printf("%lf\t",answers[i]);
		}
		printf("\n");
		for (int i = 0;i<y;i++)
		{
			sum+= (xes[i]-answers[i])*(xes[i]-answers[i]);
		}
		double dispersion = sqrt(sum/y);
		printf("Gauss method dispersion is %lf\n",dispersion);

	}


	free(mat.matrix);
	free(mat.free_coefficients);
	free(xes);
	free(answers);
	getch();

	return 0;
}