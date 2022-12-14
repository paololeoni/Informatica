#include <iostream>


void intestazione(){
    
    cout << endl;
    cout << "\tEsame Informatica 2023" << endl;
    cout << "\tNome: Paolo;   " << "Cognome: Leoni;   " << "Numero di matricola: 990447" << endl << endl;
    
}


void initialize_myarray_0 (myArray *cz) {
    cz->size = 0; 
    cz->used = 0; 
    cz->raw = NULL; 
}

void initialize_myArray (myArray *cz, int dim) {
    cz->size = dim; 
    cz->used = 0; 
    cz->raw = new <STRUCT> [dim];
}

void resize_myArray (myArray *cz, int newsize) {
    <STRUCT> * appo;
    if (newsize>(cz->size)) {
        appo = new <STRUCT> [newsize];
        memcpy ((void *) appo, (void *) cz->raw, cz->size * sizeof (<STRUCT>));
        delete [] cz->raw;
        cz->raw = appo;
    }
    if (newsize<cz->size) {
        appo = new <STRUCT> [newsize];
        memcpy ((void *) appo, (void *) cz->raw, newsize * sizeof (<STRUCT>));
        delete [] cz->raw;
        cz->raw = appo;
    }
    cz->size = newsize;
}

void deepcopy_myArray (myArray *Z1, myArray *cz2){
    cz2->size = Z1->size;
    cz2->used = Z1->used;
    cz2->raw = new <STRUCT> [Z1->size];
    memcpy ((void *) cz2->raw, (void *) Z1->raw, Z1->size * sizeof (<STRUCT>));
}

void delete_myArray (myArray *cz) {
    cz->size = 0;
    cz->used = 0;
    cz->raw = NULL;
    delete [] cz->raw;
}

// --- RAW --- 

void insert_myArray (myArray *cz, <STRUCT> Z1) {
    if (cz->used == cz->size) {
        resize_myArray (cz, (cz->size+INCR));
    }
    cz->raw[cz->used] = Z1;
    (cz->used)++;
}

void fill_myArray (myArray *cz, const char nomefile_in[]) {
    ifstream flusso_in;
    flusso_in.open (nomefile_in); 
    char * appo;
    for (int i=0; i<3; i++) {
        if (flusso_in.fail()) {
            cout << "\nProblema in apertura del file di input. Reinserire nome: ";
            cin >> appo;
            flusso_in.clear();
            flusso_in.open (appo);
        } 
    }
    initialize_myArray (cz, INCR);
    <STRUCT> poldo;
    flusso_in >> poldo; 
    while (! flusso_in.eof()) {
        insert_myArray (cz, poldo);
        flusso_in >> poldo; 
    }
}

void insert_eliminati(myArray *eliminati, myArray *pm){

   initialize_myArray(eliminati, INCR);
   
   for (int i=0; i<pm->used; i++)
   {  
      
      double d = sqrt(pow(pm->raw[i].x,2)+pow(pm->raw[i].y,2)); //condizione per la quale voglio scartare alcuni elementi del myarray 
      
      if (//condizione){
         insert_myArray(eliminati, pm->raw[i]);
         remove_at_myArray(pm,i);
      }
      
   }
}

void insert_at_myArray (myArray *cz, <STRUCT> Z1, int pos) {
    if (cz->used == cz->size) {
        resize_myArray (cz, (cz->size+1));
    }
    cz->raw[pos] = Z1;
    (cz->used)++;
    for (int i=pos; i<(cz->size-1); i++) { 
        cz->raw[i+1] = cz->raw[i]; 
    }   
}

void remove_at_myArray (myArray *cz, int pos) {
    for (int i=pos; i<(cz->size-1); i++) { 
        cz->raw[i] = cz->raw[i+1]; 
    }   
    (cz->used)--;
}

<STRUCT> seek_myArray (myArray *cz, int pos) {
    return cz->raw[pos]; 
}

void merge_sort(int a[],int low,int high){ 
    int mid; 
    if(low<high) { 
  mid = low + (high-low)/2; //This avoids overflow when low, high are too large 
  merge_sort(a,low,mid); 
  merge_sort(a,mid+1,high); 
  merge(a,low,mid,high); 
  } 
 }
  
void merge(double a[],int low,int mid,int high){ 
 //low: indice piu` piccolo dell'array da fondere 
 //mid: mezzo dell'array da fondere 
 //high: indice piu` grande dell'array da fondere 
  
  int h,i,j,k; 
  double *b; //Abbiamo bisogno di un vettore di appoggio dove copiare i dati 
  h=low; //Indice libero per scandire vettore di sinistra 
  i=0; //Indica la prima posizione libera dell'array in cui stiamo copiando i dati 
  j=mid+1; //Indice libero per scandire vettore di destra 
  
  b = new double[high-low+1]; 
  
  
  while((h<=mid)&&(j<=high)){ //Mentre non hai esaurito uno dei due sottovettori 
  if(a[h]<=a[j]){ 
    b[i]=a[h]; 
    h++; //Avanza di uno con l'indice libero dell'array di sinistra 
  } 
  else{ 
    b[i]=a[j]; 
    j++; //Avanza di uno con l'indice libero dell'array di destra 
  } 
  i++; // 
  } 
  
  if(h>mid){ //Se hai esaurito il sottovettore di sinistra, riversa in b quanto rimane del sottovettore di destra 
    for(k=j;k<=high;k++){ 
        b[i]=a[k]; 
        i++; 
    } 
  } 
  else{ 
    for(k=h;k<=mid;k++){ //Se hai esaurito il sottovettore di destra, riversa in b quanto rimane del sottovettore di sinistra 
        b[i]=a[k]; 
        i++; 
    } 
  }
  i=0;
  for(k=low;k<=high;k++,i++) {
    a[k]=b[i];
  }
  delete []b;
  b=NULL; 
}

void selection_sort(myArray *pm, int N) {

  int i, j, min;
  punto temp;

  for (i = 0; i < N - 1; i++) {

    min = i;

    for (j = i + 1; j < N; j++)
      if (pm->raw[j].m > pm->raw[min].m) {
        min = j;
      }

    temp = pm->raw[min];
    pm->raw[min] = pm->raw[i];
    pm->raw[i] = temp;
  }
}
	      
void selection_sort_out(myArray *pm, int N) { //per riordinare in base ad un campo NON della struct

  int i, j, min;
  punto temp;
  <type> appo;
  <type> f[pm->used];

  for (int i = 0; i < pm->used; i++) { //creazione array di appoggio per riordinare 
    f[i] = //formula; 
  }

  for (i = 0; i < N - 1; i++) {
    min = i;

    for (j = i + 1; j < N; j++) {
      if (f[j] < f[min]) {
        min = j;
      }
    }

    temp = pm->raw[min];
    pm->raw[min] = pm->raw[i];
    pm->raw[i] = temp;

    appo = f[min];
    f[min] = f[i];
    f[i] = appo;
  }
}



int pos_min_myArray(myArray *pm) { //N.B. se return appo: occhio al codominio
    
    float appo = pm->raw[0].x; 
    int pos{}; 
    for (int i=1; i<pm->used; i++) {
        if (pm->raw[i].x < appo) {
            appo = pm->raw[i].x;
            pos = i + 1; 
        } 
    }
    return pos; 
    //return appo;
}

int pos_max_myArray(myArray *pm) { //N.B. se return appo: occhio al codominio

    float appo = pm->raw[0].x; 
    int pos = 0; 
    for (int i=1; i<pm->used; i++) {
        if (pm->raw[i].x > appo) {
            appo = pm->raw[i].x ;
            pos = i+1; 
        } 
    }
    return pos; 
    //return appo;
}

void print_ov_myArray (myArray pm) {
    cout << "Informazioni relative alle particelle: ";     
    for (int i=0; i<pm.used; i++) {
        cout << "elemento [" << (i+1) << "] = (";
        cout << setw (4) << "POSIZIONE SU X= "<< pm.raw[i].x << ", ";
        cout << setw (4) << "POSIZIONE SU Y= "<< pm.raw[i].y << ", ";
        cout << setw (4) << "VELOCTA SU X= "<< pm.raw[i].vx << ", ";
        cout << setw (4) << "VELOCITA SU Y= "<< pm.raw[i].vy << ")" << endl;
    }
    cout << endl;
}

void print_ov_of_myArray(myArray pm, const char nomefile_out[]){


    ofstream flussout;
    flussout.open(nomefile_out);

    char * appo;
    for (int i=0; i<3; i++) {
        if (flussout.fail()) {
            cout << "\nProblema in apertura del file di input. Reinserire nome: ";
            cin >> appo;
            flussout.clear();
            flussout.open (appo);
        } 
    }
    
    flussout << "Informazioni relative agli elementi: ";

    for (int i=0; i<pm.used; i++) {
        flussout << "elemento [" << (i+1) << "] = (";
        flussout << setw (4) << "POSIZIONE SU X= "<< pm.raw[i].x << ", ";
        flussout << setw (4) << "POSIZIONE SU Y= "<< pm.raw[i].y << ", ";
        flussout << setw (4) << "VELOCTA SU X= "<< pm.raw[i].vx << ", ";
        flussout << setw (4) << "VELOCITA SU Y= "<< pm.raw[i].vy << ")" << endl;
    }

    flussout << endl;
    flussout.clear();
    flussout.close();

    cout << "Informazioni relative alle elementi: ";     
    for (int i=0; i<pm.used; i++) {
        cout << "elemento [" << (i+1) << "] = (";
        cout << setw (4) << "POSIZIONE SU X= "<< pm.raw[i].x << ", ";
        cout << setw (4) << "POSIZIONE SU Y= "<< pm.raw[i].y << ", ";
        cout << setw (4) << "VELOCTA SU X= "<< pm.raw[i].vx << ", ";
        cout << setw (4) << "VELOCITA SU Y= "<< pm.raw[i].vy << ")" << endl;
    }
    cout << endl;

}
	    
void print_ov_of_myArray_sorted(myArray pm, const char nomefile_out[]){


    ofstream flussout;
    flussout.open(nomefile_out, ios::app);

    char * appo;
    for (int i=0; i<3; i++) {
        if (flussout.fail()) {
            cout << "\nProblema in apertura del file di input. Reinserire nome: ";
            cin >> appo;
            flussout.clear();
            flussout.open (appo);
        } 
    }
    
    flussout << "Informazioni relative agli elementi: ";

    for (int i=0; i<pm.used; i++) {
        flussout << "elemento [" << (i+1) << "] = (";
        flussout << setw (4) << "POSIZIONE SU X= "<< pm.raw[i].x << ", ";
        flussout << setw (4) << "POSIZIONE SU Y= "<< pm.raw[i].y << ", ";
        flussout << setw (4) << "VELOCTA SU X= "<< pm.raw[i].vx << ", ";
        flussout << setw (4) << "VELOCITA SU Y= "<< pm.raw[i].vy << ")" << endl;
    }

    flussout << endl;
    flussout.clear();
    flussout.close();

    cout << "Informazioni relative alle elementi: ";     
    for (int i=0; i<pm.used; i++) {
        cout << "elemento [" << (i+1) << "] = (";
        cout << setw (4) << "POSIZIONE SU X= "<< pm.raw[i].x << ", ";
        cout << setw (4) << "POSIZIONE SU Y= "<< pm.raw[i].y << ", ";
        cout << setw (4) << "VELOCTA SU X= "<< pm.raw[i].vx << ", ";
        cout << setw (4) << "VELOCITA SU Y= "<< pm.raw[i].vy << ")" << endl;
    }
    cout << endl;

}

	      
