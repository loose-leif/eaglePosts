
// ff

// 10 Point Data Loader for HV507

 const byte CLK = 4;
 const byte LAT= 10;
 const byte DATA= 9;
 const byte DIR = 12;
 const byte BLANK = 8;
 const byte POL = 7;
 const byte pause = 2;
 const byte HOLDHIGH = 13;
 const int runCount = 8;
 const int width = 8;
 

 //const int pad_count = 64;
 //const int packet_count = 2;

const int HV_size = 64;

int i;

int k;

int runNum;

int out[] = {1,1,1,1,1,1,1,1};
                    
// EXAMPLE FULL HOLD int output[8] = {96,24,0,0,0,0,8,137};

int outputArray[runCount][width] = 
                        
                        {  {64,0,0,0,0,0,0,0},
                           {192,0,0,0,0,0,0,0},
                           {192,0,0,0,0,0,0,2},
                           {64,0,0,0,0,0,0,2},
                           {64,0,0,0,0,0,1,2},
                           {64,0,0,0,0,0,1,0},
                           {64,0,0,0,0,0,17,0},
                           {64,0,0,0,0,0,16,0} };
                        


                
// ----TEMPLATE--------> 1 { 1,1,0,0,0,0,0,0, 8
//                       9   0,0,1,1,0,0,0,0, 16
//                      17   0,0,0,0,0,0,0,0, 24
//                      28   0,0,0,0,0,0,0,0, 32
//                      33   0,0,0,0,0,0,0,0, 40
//                      41   0,0,0,0,0,0,0,0, 48
//                      49   0,0,0,1,0,0,0,1, 56
//                      57   0,0,0,1,0,0,1,0  64 };


//1 0,1,0,0,0,0,0,0 [2 IS PERM ON] int 64

//2 1,1,0,0,0,0,0,0 2->1 int 192

//3 1,1,0,0,0,0,0,0 int 192
//  0,0,0,0,0,0,1,0 1&2->63 int 2

//4 0,1,0,0,0,0,0,0 [2 IS PERM ON] int 64
//  0,0,0,0,0,0,1,0 63 int 2

//5 0,1,0,0,0,0,0,0 [2 IS PERM ON] int 64
//  0,0,0,0,0,0,1,0  int 2
//  0,0,0,0,0,0,0,1 63->56 int 1

//6 0,1,0,0,0,0,0,0 [2 IS PERM ON] int 64
//  0,0,0,0,0,0,0,1 56 int 1

//7 0,1,0,0,0,0,0,0 [2 IS PERM ON] int 64
//  0,0,0,1,0,0,0,1 56->52 int 17

//8 0,0,0,1,0,0,0,0 52 int 16

// END OF DEMO! 8 STEPS THROUGH

// 0,0,0,1,0,0,0,0 int 16
// 0,0,0,1,0,0,0,0 52->60 int 16

// 0,0,0,1,0,0,0,0 60 int 16

// 0,0,0,1,0,0,0,0 int 16
// 0,0,1,0,0,0,0,0 60->11 int 32

// 0,0,1,0,0,0,0,0 11 int 32

// 0,0,1,1,0,0,0,0 11->12

// 0,0,0,1,0,0,0,0 12


 // top rez F0I0 pin 42, HV507 2
 // top bridge B0I0 pin 43, HV507 1
 // 
 // movement pads 0 -> 3
 //
 // pad0 = PAD25 pin23, HV507 63
 // pad1 = PAD24 pin16, HV507 56 
 // pad2 = PAD23 pin12, HV507 52
 // pad3 = PAD7 pin20, HV507 60
 // 
 // side bridge B2I0 pin51, HV507 11
 // side rez F2I0 pin52, HV507 12
  
void setup (){

  pinMode(LAT, OUTPUT);

  pinMode(DATA, OUTPUT);

  pinMode(DIR, OUTPUT);

  pinMode (CLK, OUTPUT);

  pinMode(BLANK, OUTPUT); 

  pinMode(POL, OUTPUT);

  pinMode(pause, INPUT);

  pinMode(HOLDHIGH, OUTPUT);

  digitalWrite(LAT, 0);

  digitalWrite(DIR, 0);

  digitalWrite(POL, 1);

  digitalWrite(BLANK, 1);

  digitalWrite(HOLDHIGH, 1);
  
  Serial.begin(9600);

  while(digitalRead(pause));

}

void loop (){
    
    for(runNum=0; runNum<runCount; runNum++){

    Serial.print("Run: ");
    Serial.print(runNum);
    Serial.println();

    for(k=0;k<8;k++){
    
    Serial.print(outputArray[runNum][k]+256,BIN);

    Serial.println();

    }

    Serial.println();
  
    delay(1000);

    digitalWrite(LAT,1);

    for(i = 0; i<width; i++){
      
      shiftOut(DATA, CLK, MSBFIRST, outputArray[runNum][i]);

    }

    digitalWrite(LAT,0);
    
    while(digitalRead(pause));
    
    }
    
}
