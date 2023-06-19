#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int main() {
    char screen[465];
	char screen2[465];
	char screen3[465];
	char screen4[465];
    	int i = 0 ;
    	while(i<465){
	    	if(i%31 == 30){
		    	screen[i] = '\n';
	    	}
			else{
				screen[i] = ' ';
	    		if(i%31 == 0){
		    		screen[i] = '#';
	    		}
				else if(i%31 == 29){
					screen[i] = '#';
				}
				else if(i <= 28){
					screen[i] = '#';
				}
				else if(i >= 434){
					screen[i] = '#';
				}
			}
	    	i=i+1;
			char msg1[8]="Tungsten";
			int a = 0;
			while(a<8)
			{
				screen[a+10+31*3] = msg1[a];
				a++;
			}
			char msg2[11]="1.Play Game";
			int b = 0;
			while(b<11)
			{
				screen[b+3+31*6] = msg2[b];
				b++;
			}
				char msg3[14]="2.How To Play?";
				int c = 0;
			while(c<14)
			{
				screen[c+3+31*9] = msg3[c];
				c++;
			}
			char msg4[6]="3.Exit";
			int d = 0;
			while(d<6)
			{
				screen[d+3+31*12] = msg4[d];
				d++;
			}
		}
    	int i2 = 0 ;
    	while(i2<465){
	    	if(i2%31 == 30){
		    	screen2[i2] = '\n';
	    	}
			else{
					screen2[i2] = ' ';
	    		if(i2%31 == 0){
		    		screen2[i2] = '#';
	    		}
				else if(i2%31 == 29){
					screen2[i2] = '#';
				}
				else if(i2 <= 28){
					screen2[i2] = '#';
				}	
				else if(i2 >= 434){
					screen2[i2] = '#';
				}
			}
	    	i2=i2+1;
			char msg5[5]="SORRY";
			int e = 0;
			while(e<5)
			{
				screen2[e+13+31*3] = msg5[e];
				e++;
			}
			char msg6[21]="This function has not";
			int f = 0;
			while(f<21)
			{
				screen2[f+5+31*7] = msg6[f];
				f++;
			}
			char msg7[21]="yet been implemented.";
			int g = 0;
			while(g<21)
			{
				screen2[g+5+31*8] = msg7[g];
				g++;
			}
			char msg8[15]="Press 1 to back";
			int h = 0;
			while(h<15)
			{
				screen2[h+5+31*9] = msg8[h];
				h++;
			}
    	}
    		int i3 = 0 ;
    		while(i3<465){
	    		if(i3%31 == 30){
		   			screen3[i3] = '\n';
	    		}
				else{
					screen3[i3] = ' ';
	    		if(i3%31 == 0){
		    		screen3[i3] = '#';
	    		}
				else if(i3%31 == 29){
					screen3[i3] = '#';
				}
				else if(i3 <= 28){
					screen3[i3] = '#';
				}
				else if(i3 >= 434){
					screen3[i3] = '#';
				}
			}
	    	i3=i3+1;
			char msg9[17]="How To Play Game?";
			int j = 0;
			while(j<17)
			{
				screen3[j+7+31*3] = msg9[j];
				j++;
			}
			char msg10[20]="Press your space bar";
			int k = 0;
			while(k<20)
			{
				screen3[k+5+31*7] = msg10[k];
				k++;
			}
			char msg11[24]="to be able to dig up ore";
			int l = 0;
			while(l<24)
			{
				screen3[l+2+31*8] = msg11[l];
				l++;
			}
			char msg12[15]="Press 1 to back";
			int n = 0;
			while(n<15)
			{
				screen3[n+5+31*9] = msg12[n];
				n++;
			}
    	}
    	int i4 = 0 ;
    	while(i4<465){
	    	if(i4%31 == 30){
		    	screen4[i4] = '\n';
	    	}
			else{
				screen4[i4] = ' ';
	    		if(i4%31 == 0){
		    		screen4[i4] = '#';
	    		}
				else if(i4%31 == 29){
					screen4[i4] = '#';
				}
				else if(i4 <= 28){
					screen4[i4] = '#';
				}
				else if(i4 >= 434){
					screen4[i4] = '#';
				}
			}
	    	i4=i4+1;
			char msg13[23]="Are you really going to";
			int m = 0;
			while(m<23)
			{
				screen4[m+3+31*3] = msg13[m];
				m++;
			}
			char msg14[13]="end the game?";
			int o = 0;
			while(o<13)
			{
				screen4[o+3+31*4] = msg14[o];
				o++;
			}
			char msg15[5]="1.Yes";
			int p = 0;
			while(p<5)
			{
				screen4[p+3+31*10] = msg15[p];
				p++;
			}
			char msg16[4]="2.No";
			int q = 0;
			while(q<4)
			{
				screen4[q+3+31*11] = msg16[q];
				q++;
			}
    	}
		int ctl = 0;
		while(screen){
			printf("%s",screen);
			printf("Press key-->");
			scanf("%d", &ctl);
			if(ctl == 1){
				while(screen2){
					ctl = 0;
					printf("%s", screen2);
					scanf("%d", &ctl);
					if(ctl == 1){
						ctl = 0;
						break;
					}
				}
			}
			else if(ctl == 2){
				while(ctl){
					ctl = 0;
					printf("%s", screen3);
					scanf("%d", &ctl);
					if(ctl == 1){
						ctl = 0;
						break;
					}
					else if(ctl == 2){
						continue;
					}
				}
			}
			else if(ctl == 3){
				ctl = 0;
				printf("%s", screen4);
				scanf("%d", &ctl);
				if(ctl == 1){
					ctl = 0;
					break;
				}
				else if(ctl == 2){
					continue;
				}
			}
				}
		screen[464] = '\0';
		screen2[464] = '\0';
		screen3[464] = '\0';
    	screen4[464] = '\0';
    return 0;
}
