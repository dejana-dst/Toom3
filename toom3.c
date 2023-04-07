#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DUZ 50000   // maksimalni broj cifara velikog broja, tj. duzina nizova u kojima pamtimo brojeve
#define BAZA 10000 //0  //osnova brojnog sistema



int unesi(int x[]){
    int j=0,i=0,c, y[4*DUZ], znak=1,q=10;
    printf("Unesi broj: ");
    c=getchar();
    if(c==45){ // ako je prvi simbol znak "-" onda se mjenja znak broja
        znak=-1;c=getchar();
    }
    while(c!=10){
        y[i]=c-48; // ASSCI vrjednost broja pretvaramo u sam broj
        c=getchar();
        i++;
    }
    i--;
    c=y[i];i--;
    while(i>=0){ // na osnovu pomocnog niza formira broj zapamcen u zeljenoj osnovi
        if(q<BAZA){
            c+=y[i]*q;
            q*=10;
            i--;
        }else{
            j++;
            x[j]=c;
            q=10;
            c=y[i];
            i--;
        }
    }
    j++;x[j]=c;x[0]=znak*j;
    return x[0];
}  //unesi(int x[])

// prikazuje cifre velikog broja
void prikazi(int x[]){
    printf("\t");
    int i,x0,p=BAZA/10;
    x0=abs(x[0]);
    if(x[0]<0 && 1)
     //  !(x[0]==-1 && x[1]==0))
            printf(" -"); // ako je broj negativan prvo prikazemo znak
    i=x0;
    while (x[i]==0 && i>1)
    {
        i--;
    }

    printf("%d ",x[i]);


    for(i=i-1;i>0;i--){

        while( (p>0)&&(x[i]<p)){
            printf("0");p=p/10;
        }

        if(x[i]!=0) printf("%d ",x[i]);
        else  printf(" ");
        p=BAZA/10;
    }


    printf("\n");
} // prikazi(int x[])


void azbir(int x[],int y[],int z[]){  // racuna  z=|x|+|y|
    int prenos=0,x0,y0,i;
    x0=abs(x[0]);y0=abs(y[0]);
    if(x0>y0){ // ako broj x ima vise cifara, onda dodaj prvo cifre broja y, a zatim nastavi samo sa prenosom
        for(i=1;i<=y0;i++){
            z[i]=x[i]+y[i]+prenos;
            if(z[i]>=BAZA){
                prenos=1; z[i]-=BAZA;
            }
            else prenos=0;
        }
        for(i=y0+1;i<=x0;i++){
            z[i]=x[i]+prenos;
            if(z[i]>=BAZA){
                prenos=1; z[i]-=BAZA;
            }
            else prenos=0;
        }
        if(prenos>0){
            z[x0+1]=prenos;
            z[0]=x0+1;
        }else z[0]=x0;
    }
    else{  // ako broj y ima vise cifara
        for(i=1;i<=x0;i++){
            z[i]=x[i]+y[i]+prenos;
            if(z[i]>=BAZA){
                prenos=1; z[i]-=BAZA;
            }
            else prenos=0;
        }
        for(i=x0+1;i<=y0;i++){
            z[i]=y[i]+prenos;
            if(z[i]>=BAZA){
                prenos=1; z[i]-=BAZA;
            }
            else prenos=0;
        }
        if(prenos>0){
            z[y0+1]=prenos;
            z[0]=y0+1;
        }else z[0]=y0;
    }
}

int arazlika(int x[],int y[],int z[]){ // racuna z=| |x|-|y| |
    int x0,y0,z0,i,pozajmica=0,veci=1;  // vraca 0 ako je x=y, 1 ako je |x|>|y| inace 2
    x0=abs(x[0]);y0=abs(y[0]);
    if(x0==y0){ // ako brojevi imaju isti broj cifara
        while((x0>0)&&(x[x0]==y[x0]))x0--; // cifra najvece tezine su iste pa oduzimanjem se gube
        if(x0==0){
            z0=1;z[1]=0;veci=0; // u slucaju da su brojevi jednaki rezultat je z=0
        }
        else{
            if(x[x0]>y[x0]){ // prvi broj je veci jer ima vacu cifru pa racunamo z=x-y
                for(i=1;i<=x0;i++){
                    z[i]=x[i]-y[i]-pozajmica;
                    if(z[i]<0){
                        pozajmica=1; z[i]+=BAZA;
                    }
                    else pozajmica=0;
                }
                z0=x0;
            }
            else{ // drugi broj veci, pa racunamo  z=y-x
                veci=2;
               for(i=1;i<=x0;i++){
                    z[i]=y[i]-x[i]-pozajmica;
                    if(z[i]<0){
                        pozajmica=1; z[i]+=BAZA;
                    }
                    else pozajmica=0;
                }
                z0=x0;
            }
        }
    }
    else{ //jedan od brojeva ima vise cifara
        if(x0>y0){ //prvi broj ima vise cifara tj. veci je pa racunamo  z=x-y
            for(i=1;i<=y0;i++){
                z[i]=x[i]-y[i]-pozajmica;
                if(z[i]<0){
                    pozajmica=1; z[i]+=BAZA;
                }
                else pozajmica=0;
            }
            for(i=y0+1;i<=x0;i++){
                z[i]=x[i]-pozajmica;
                if(z[i]<0){
                    pozajmica=1; z[i]+=BAZA;
                }
                else pozajmica=0;
            }
            z0=x0;
        }
        else{ // drugi broj ima vise cifara pa racunamo   z=y-x
            veci=2;
            for(i=1;i<=x0;i++){
                z[i]=y[i]-x[i]-pozajmica;
                if(z[i]<0){
                    pozajmica=1; z[i]+=BAZA;
                }
                else pozajmica=0;
            }
            for(i=x0+1;i<=y0;i++){
                z[i]=y[i]-pozajmica;
                if(z[i]<0){
                    pozajmica=1; z[i]+=BAZA;
                }
                else pozajmica=0;
            }
            z0=y0;
        }
    }
    while((z0>1)&&(z[z0]==0))z0--;
    z[0]=z0;
    return veci;
} // int arazlika(int x[],int y[],int z[])


void zbir(int x[],int y[],int z[]){ // racuna z=x+y sa znakom
    int x0,y0,veci;
    x0=x[0];y0=y[0];
    if(x0*y0>0){  // ako su oba broja istog znaka onda ih  sabiramo i dodajemo odgovarajuci znak
        azbir(x,y,z);
        if(x0<0) z[0]*=(-1);
    }
    else{ // ako su brojevi razlicitog znaka, onda ih  oduzimamo i upisujemo znak veceg
        veci=arazlika(x,y,z);
        if(((veci==1)&&(x0<0))||((veci==2)&&(y0<0))) z[0]*=(-1);
    }
}

void skolskomnoz(int x[],int y[],int z[]){ //racuna z=x*y koristeci jednostavan algoritam
    int x0,y0,z0,i,j,znak=1;
    x0=x[0];y0=y[0];
    if(x0*y0<0)znak=-1;
    x0=abs(x0);y0=abs(y0);
    for(i=1;i<=x0+y0;i++)z[i]=0; // mnozimo cifre, svaku sa svakom
    for(i=1;i<=x0;i++){
        for(j=1;j<=y0;j++){
            z[i+j-1]+=x[i]*y[j];
            if(z[i+j-1]>=BAZA){
                z[i+j]+=(z[i+j-1]/BAZA);
                z[i+j-1]%=BAZA;
            }
        }
    }
    z0=x0+y0;
    while((z0>1)&&(z[z0]==0))z0--;
    z[0]=znak*z0;
}


// vrsi formiranje novog broja y tako sto prepise cifre broja x od pozicije i1 do pozicije i2
void prepisi(int x[],int y[], int i1, int i2){
    int i;
    if(i1<=i2){
        for(i=i1;i<=i2;i++)y[i-i1+1]=x[i];
        y[0]=i2-i1+1;
        while((y[0]>1)&&(y[y[0]]==0))y[0]--;
        /*if(x[0]<0)
            y[0]*=-1;*/
    }
    else{
        y[0]=1;y[1]=0;
    }

}





void dijeliCifra(int x[],int z[],int c) //z=x/c
{
    int i=abs(x[0]),prenos=0;
    int *y;
    y= (int *) calloc(abs(z[0])+1,sizeof(int));
    if(x[i]<c)
    {
        prenos=x[i];
        for(i=i-1;i>0;i--)
        {
            y[i]=((BAZA*prenos)+x[i])/c;
            prenos=((BAZA*prenos)+x[i])%c;
        }
        y[0] = (x[0] < 0) ? (x[0]+1) : (x[0]-1);
    }
    else
    {
        while(i>0)
        {
            y[i]=((BAZA*prenos)+x[i])/c;
            prenos=((BAZA*prenos)+x[i])%c;
            i--;
        }
        y[0] = x[0];
    }

    for(i=1;i<=abs(y[0]);i++)
        z[i]=y[i];
    z[0]=y[0];
    while((z[0]>1)&&(z[z[0]]==0))z[0]--;

}



/************************************/
void zbirpom(int x[],int y[], int pomeraj,int z[]){
    // racuna zbir s pomerajem drugog broja tj. z=x+ y*BAZA^pomeraj
    int *yn, y0,i;
    y0=abs(y[0]);
    yn= (int *) calloc((pomeraj+y0+1),sizeof(int));
    for(i=1;i<=pomeraj; i++) yn[i]=0;
    for(i=1;i<=y0; i++) yn[pomeraj+i]=y[i];
    yn[0]=y0+pomeraj;
    if(y[0]<0) yn[0]*=(-1);
    zbir(x,yn,z);
    free(yn);
}

void zerocheck (int x[])
{
    int i;
    for(i=1;i<=abs(x[0]); i++)
    {
        if(x[i]==0)
            continue;
        else
            return;
    }
        x[0]=1;

}

/*******************************/


void toom3(int x[],int y[], int z[])
{

    int znak=1,i,i1,i2;
    if(x[0]*y[0]<0) znak=-1;

    i1=(int)ceil((abs(x[0]))/3.0);
    i2= (int)ceil((abs(y[0]))/3.0);
    i = (i1 < i2) ? i2 : i1;
    //int bazaB=(int)ceil(pow(BAZA,i));
    if (i<=1)
    {
        skolskomnoz(x,y,z);
        return;
    }

    if (abs(x[0])==1 || abs(y[0])==1)
    {
        skolskomnoz(x,y,z);
        return;
    }

    if (abs(x[0])<=2*i && abs(y[0])<=2*i)
    {
        skolskomnoz(x,y,z);
        return;
    }
     //SPLITTING
    int *x0,*x1,*x2,*y0,*y1,*y2;
    x0= (int *) calloc(i+1,sizeof(int));
    x1= (int *) calloc(i+1,sizeof(int));
    x2= (int *) calloc(i+1,sizeof(int));
    y0= (int *) calloc(i+1,sizeof(int));
    y1= (int *) calloc(i+1,sizeof(int));
    y2= (int *) calloc(i+1,sizeof(int));

    // nebalansirano?
    if( (abs(x[0])<=i))
    { //x ima samo jedan krak
        prepisi(x,x0,1,abs(x[0]));
        x1[0]=1;
        x1[1]=0;
        x2[0]=1;
        x2[1]=0;

    }
    else if((abs(x[0])<=2*i))
    {
        //x ima dva kraka
        prepisi(x,x0,1,i);
        prepisi(x,x1,i+1,abs(x[0]));
        x2[0]=1;
        x2[1]=0;
    }
    else
    {
        prepisi(x,x0,1,i);
        prepisi(x,x1,i+1,i+i);
        prepisi(x,x2,i+i+1,abs(x[0]));
    }


    if( (abs(y[0])<=i))
    { //y ima samo jedan krak
        prepisi(y,y0,1,abs(y[0]));
        y1[0]=1;
        y1[1]=0;
        y2[0]=1;
        y2[1]=0;
    }
    else if((abs(y[0])<=2*i))
    {
        //y ima dva kraka
        prepisi(y,y0,1,i);
        prepisi(y,y1,i+1,abs(y[0]));
        y2[0]=1;
        y2[1]=0;
    }
    else
    {
        prepisi(y,y0,1,i);
        prepisi(y,y1,i+1,i+i);
        prepisi(y,y2,i+i+1,abs(y[0]));
    }

    //EVALUATION
    int *p0,*p1,*p_1,*p_2,*pinf,*ppom,*q0,*q1,*q_1,*q_2,*qinf,*qpom,*x1neg,*x0neg;
    p0= (int *) calloc(i+1,sizeof(int));
    p1= (int *) calloc(i+2,sizeof(int));
    p_1= (int *) calloc(i+2,sizeof(int));
    p_2= (int *) calloc(i+2,sizeof(int));
    pinf=(int *) calloc(i+1,sizeof(int));
    ppom=(int *) calloc(i+2,sizeof(int));
    q0= (int *) calloc(i+1,sizeof(int));
    q1= (int *) calloc(i+2,sizeof(int));
    q_1= (int *) calloc(i+2,sizeof(int));
    q_2= (int *) calloc(i+2,sizeof(int));
    qinf=(int *) calloc(i+1,sizeof(int));
    qpom=(int *) calloc(i+2,sizeof(int));
    x0neg=(int *) calloc(i+1,sizeof(int));
    x1neg=(int *) calloc(i+1,sizeof(int));

    zbir(x0,x2,ppom);// ppom <- x0 + x2
    prepisi(x0,p0,1,abs(x0[0])); //p(0)
    zbir(ppom,x1,p1);// p(1) <- x0+x2+x1

    prepisi(x1,x1neg,1,abs(x1[0])); // -x1
    x1neg[0]*=-1;   zerocheck(x1neg);
    zbir(ppom,x1neg,p_1); //p(-1) <- x0+x2-x1

    prepisi(x0,x0neg,1,abs(x0[0])); //-x0
    x0neg[0]*=-1;   zerocheck(x0neg);
    zbir(p_1,x2,ppom); //	p(-1)+x2
    zbir(ppom,ppom,ppom); // (p(-1)+x2) * 2
    zbir(ppom,x0neg,p_2); //p(-2) <- ppom -x0
    prepisi(x2,pinf,1,abs(x2[0]));//p(inf)



    zbir(y0,y2,qpom);
    prepisi(y0,q0,1,abs(y0[0])); //q(0)
    zbir(qpom,y1,q1);// q(1)
    prepisi(y1,x1neg,1,abs(y1[0])); //-y1
    x1neg[0]*=-1; zerocheck(x1neg);
    zbir(qpom,x1neg,q_1); //q(-1)
    prepisi(y0,x0neg,1,abs(y0[0])); // -y0
    x0neg[0]*=-1; zerocheck(x0neg);
    zbir(q_1,y2,qpom); //	(q(−1) + y2)
    zbir(qpom,qpom,qpom);
    zbir(qpom,x0neg,q_2); //q(-2)
    prepisi(y2,qinf,1,abs(y2[0]));//q(inf)

    zerocheck(p0);
    zerocheck(p1);
    zerocheck(p_1);
    zerocheck(p_2);
    zerocheck(pinf);
    zerocheck(q0);
    zerocheck(q1);
    zerocheck(q_1);
    zerocheck(q_2);
    zerocheck(qinf);

    free(x2); free(x1); free(x0); free(y2); free(y1); free(y0);
    free(x1neg);free(x0neg);free(qpom); free(ppom);


    //POINTWISE MULTIPLICATION
    int *r0,*r1,*r_1,*r_2,*rinf;
    r0= (int *) calloc(2*i+4,sizeof(int));
    r1= (int *) calloc(2*i+4,sizeof(int));
    r_1= (int *) calloc(2*i+4,sizeof(int));
    r_2= (int *) calloc(2*i+4,sizeof(int));
    rinf=(int *) calloc(2*i+4,sizeof(int));
    toom3(p0,q0,r0);        free(p0); free(q0);
    toom3(p1,q1,r1);        free(p1);free(q1);
    toom3(p_1,q_1,r_1);     free(p_1);free(q_1);
    toom3(p_2,q_2,r_2);     free(p_2); free(q_2);
    toom3(pinf,qinf,rinf);  free(pinf);free(qinf);

    zerocheck(r0);
    zerocheck(r1);
    zerocheck(r_1);
    zerocheck(r_2);
    zerocheck(rinf);

    //INTERPOLATION

    int *s0,*s1,*s2,*s3,*s4,*rpom;
    s0= (int *) calloc(2*i+4,sizeof(int));
    s1= (int *) calloc(2*i+4,sizeof(int));
    s2= (int *) calloc(2*i+4,sizeof(int));
    s3= (int *) calloc(2*i+4,sizeof(int));
    s4=(int *) calloc(2*i+4,sizeof(int));
    rpom=(int *) calloc(2*i+4,sizeof(int));

    prepisi(r0,s0,1,abs(r0[0])); //s0
    prepisi(rinf,s4,1,abs(rinf[0])); //s4
    prepisi(r1,rpom,1,abs(r1[0]));
    rpom[0] = (r1[0] > 0) ? rpom[0]*(-1) : rpom[0]; zerocheck(rpom); // -r(1)
    zbir(r_2,rpom,s3); //(r(−2) − r(1))
    dijeliCifra(s3,s3,3); //s3 <- (r(−2) − r(1))/3
    prepisi(r_1,rpom,1,abs(r_1[0]));
    rpom[0] = (r_1[0] > 0) ? rpom[0]*(-1) : rpom[0];  zerocheck(rpom);      //-r(-1)
    zbir(r1,rpom,s1); // (r(1) − r(−1))
    dijeliCifra(s1,s1,2); //s1 <- (r(1) − r(−1))/2
    prepisi(r0,rpom,1,abs(r0[0]));
    rpom[0] = (r0[0] > 0) ? rpom[0]*(-1) : rpom[0]; zerocheck(rpom);//-r(0)
    zbir(r_1,rpom,s2); //r2	<- r(−1) − r(0)
    prepisi(s3,rpom,1,abs(s3[0]));
    rpom[0] = (s3[0] > 0) ? rpom[0]*(-1) : rpom[0]; zerocheck(rpom);//-s3
    zbir(s2,rpom,s3); // s2-s3
    dijeliCifra(s3,s3,2); //(s2-s3) /2
    zbir(s3,rinf,s3);
    zbir(s3,rinf,s3); //s3 <- (s2 − s3)/2 + 2r(inf)
    prepisi(s4,rpom,1,abs(s4[0]));
    rpom[0] = (s4[0] > 0) ? rpom[0]*(-1) : rpom[0]; zerocheck(rpom);// -s4
    zbir(s2,s1,s2); // s2+s1
    zbir(s2,rpom,s2); //(s2+s1)-s4
    prepisi(s3,rpom,1,abs(s3[0]));
    rpom[0] = (s3[0] > 0) ? rpom[0]*(-1) : rpom[0];    zerocheck(rpom); // -s3
    zbir(s1,rpom,s1); //s1 <- s1 − s3

    zerocheck(s0);
    zerocheck(s1);
    zerocheck(s2);
    zerocheck(s3);
    zerocheck(s4);

    free(r0); free(r1); free(r_1); free(r_2);free(rinf);free(rpom);
    //RECOMPOSITION

    int *rez;
    rez= (int *) calloc(6*i+1,sizeof(int));

    zbirpom(s0,s1,i,rez);
    zbirpom(rez,s2,2*i,rez);
    zbirpom(rez,s3,3*i,rez);
    zbirpom(rez,s4,4*i,rez);

    free(s0); free(s1); free(s2); free(s3);free(s4);

    prepisi(rez,z,1,abs(rez[0]));
    z[0]*=znak;

    free(rez);
}





int main()
{
    char izbor='y';
    int a[DUZ],b[DUZ],c[DUZ];
    do
    {
        unesi(a);
        unesi(b);
        printf("Prvi broj: ");prikazi(a);
        printf("\nDrugi broj: "); prikazi(b);
        printf("\n\nRezultat:\n");
        toom3(a,b,c);
        prikazi(c);
        printf("Novi brojevi? y/n \n");
        scanf("%s",&izbor);
        getchar();

    } while (izbor!='n' && izbor!='N');



    return 0;
}
