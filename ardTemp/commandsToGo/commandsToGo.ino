
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

 

 //const int pad_count = 64;
 //const int packet_count = 2;

const int HV_size = 64;

int i;

int runNum;
                    
// EXAMPLE FULL HOLD int output[8] = {96,24,0,0,0,0,8,137};

int outputArray[8][8] = {{96,0,0,0,0,0,0,0},
                         {0,24,0,0,0,0,0,0},
                         {0,0,0,0,0,0,8,0},
                         {0,0,0,0,0,0,0,137},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0}};

                
// --------------------> 0 { 0,1,1,0,0,0,0,0, 7
//                       8   0,0,0,1,1,0,0,0, 15
//                      16   0,0,0,0,0,0,0,0, 23
//                      24   0,0,0,0,0,0,0,0, 31
//                      32   0,0,0,0,0,0,0,0, 39
//                      40   0,0,0,0,0,0,0,0, 47
//                      48   0,0,0,0,1,0,0,0, 55
//                      56   1,0,0,0,1,0,0,1  63 };

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

}

void loop (){

    for(runNum=0; runNum<8; runNum++){
    
    for(i = 0; i<8; i++){
      
      shiftOut(DATA, CLK, MSBFIRST, outputArray[runNum][i]);

    }
    
    while(digitalRead(pause));
    delay(1000);
    Serial.print(runNum);
    }

    

    //Serial.print("new push\n");
    
}
