#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"


//structure pour la matrice clé
typedef struct 
{
   int x;
   int y;
}ke;


//nombre des itérations
// const int iterations= 1;



int main(void) {
  
    int width, height, channels;
    char img_name[150] ; 
    int iterations  ; 

    //enter image name or path
    printf("Enter the image name or path : ") ; 
    scanf("%s" , &img_name) ; 


    //load the image
    unsigned char *img = stbi_load(img_name, &width, &height, &channels, 0);


    //check if the image is loaded successfully
    if(img == NULL) {
        printf("Error in loading the image\n");
        for(int i = 0; i < 8000000; i++);
        exit(1);
    }
    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

    //inter the number of iterations 
    printf("Set the number of iterations : ")  ; 
    scanf("%i",  &iterations) ;

    //put the orginal image in a matrix
    unsigned char **crypted_image_matrix = malloc(sizeof(unsigned char *)*height);
    for(int i = 0; i < height; i++)
        crypted_image_matrix[i] = malloc(sizeof(unsigned char)*width*channels);
        
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width*channels; j++)
            crypted_image_matrix[i][j] = img[i*width*channels + j];
    }

    //liberer le tableau dynamique pour optimiser la mémoire
    free(img);

    //creation of key matrix
    ke **R=malloc(sizeof(ke *)*height);
    for(int i = 0; i < height; i++)
        R[i] = malloc(sizeof(ke)*width);


    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            R[i][j].x= (i + j)   % height;
            R[i][j].y= (i + 2*j) % width ;               
             //printf("x=%d,y=%d",R[i][j].x,R[i][j].y);
        }
    }


    //creation de la variable de la matrice image
    unsigned char **image_original_matrix = malloc(sizeof(unsigned char *)*height);
    for(int i = 0; i < height; i++)
        image_original_matrix[i] = malloc(sizeof(unsigned char)*width*channels);
    printf("channels=%d",channels);

    int counter=0;
    while(counter<iterations) {
       for(int i = 0; i < height; i++){
           for(int j = 0; j < width*channels; j=j+channels){
                int s=j/channels;
                int nx=R[i][s].x;
                int ny=R[i][s].y;
                //printf("nx=%d,ny=%d",nx,ny);

                for(int k = 0; k < channels ; k++){
                    image_original_matrix[i][j+k]=crypted_image_matrix[nx][(ny)*channels+k];
                }  
            }
        }
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width*channels; j++)
                crypted_image_matrix[i][j] = image_original_matrix[i][j];
           
                
        }
        counter++;
    }
    unsigned char *nimg = malloc(sizeof(unsigned char)*height*width*channels);


    //changement de la matrice en un tableau dynamique
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width*channels; j++)
            nimg[i*width*channels + j]=image_original_matrix[i][j] ;
    }

    //affichage de l'image
    
    stbi_write_jpg("decrypted_img.jpg", width, height, channels, nimg, 100);


    

return 0;


}





