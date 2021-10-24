
 // ff

 // Multi-step Loader for HV507 Shift-Registers

 // PINS FOR HARDWARE
 
 const byte CLK = 4;
 const byte LAT= 10;
 const byte DATA= 9;
 const byte DIR = 12;
 const byte BLANK = 8;
 const byte POL = 7;
 const byte pause = 2;
 const byte HOLDHIGH = 13;

 // TEST PARAMETERS
 
 const int runCount = 8; // how many time steps will be used
 const int width = 8; // how many values to be passed with each time-step
 const int HV_size = 64; // amount of bit values in shift register
 int runNum; // the current time-step
 int i; // a basic iterator     

 //const int pad_count = 64;

 int runArray[runCount][width] = 

                         // this structure currently includes 8 runs aka 8 time steps
                         
                         // each given array has 8 entries of 8 bit values (0-255), meaning
                         // 64 total bits to be communicated to the HV507

                         // for outputArray[0][0] you see it has the value of 64, which is
                         // 01000000 it will be the first 8 of 64 bits pushed to the HV507
                         // for this first array, the rest of the bits pushed will be 0's

                         // given the HV507 works as a shift register, these values will be
                         // pushed to the back end of the register once all 64 bits have been
                         // entered
                         
                        
                        {{64,0,0,0,0,0,0,0}, //1
                         {192,0,0,0,0,0,0,0},
                         {192,0,0,0,0,0,0,2}, 
                         {64,0,0,0,0,0,0,2},
                         {64,0,0,0,0,0,1,2},
                         {64,0,0,0,0,0,1,0},
                         {64,0,0,0,0,0,17,0},
                         {64,0,0,0,0,0,16,0}}; //8


                
 // ---HVOUT-TEMPLATE---> 1 { 1,1,0,0,0,0,0,0, 8
 //                       9   0,0,1,1,0,0,0,0, 16
 //                      17   0,0,0,0,0,0,0,0, 24
 //                      28   0,0,0,0,0,0,0,0, 32
 //                      33   0,0,0,0,0,0,0,0, 40
 //                      41   0,0,0,0,0,0,0,0, 48
 //                      49   0,0,0,1,0,0,0,1, 56
 //                      57   0,0,0,1,0,0,1,0  64 }; // this represents which of the 64 bits of the shift register we are
                                                     // looking to manipulate, this is simply a reference for understanding
                                                     // which integer values to enter when creating a single step
                                                     // (e.g. run step 1: {64,0,0,0,0,0,0,0}) turn on only the "01000000" 6th bit
                                                     // [0th - 7th] of the first array entry which will correspond to turning on
                                                     // the HVOUT2 pin on hardware, which is the starting rezervoir (F0I0) in this
                                                     // demo

                                                     // see how in the first row of the hvout template we have [1,1,0,0,0,0,0,0] this is showing
                                                     // that the 6th and 7th bits are of interest for knowing where the B0I0 and F0I0 pads
                                                     // are in hardware respectively


 // VERY SIMPLE STEP-BASED ROUTING ALGORITHM

 // (Xth int of runArray, this is telling you what number you should put
 // in the array used for a given time-step entry, again 8 int values
 // where each 8 bit int holds ONLY 8 bits.

 //1 0,1,0,0,0,0,0,0 [2 IS PERM ON] int 64 (0th int of runArray)

 //2 1,1,0,0,0,0,0,0 2->1 int 192 (1st int of runArray)

 //3 1,1,0,0,0,0,0,0 int 192 (1st int of runArray)
 //  0,0,0,0,0,0,1,0 1&2->63 int 2

 //4 0,1,0,0,0,0,0,0 [2 IS PERM ON] int 64 (0th int of runArray)
 //  0,0,0,0,0,0,1,0 63 int 2

 //5 0,1,0,0,0,0,0,0 [2 IS PERM ON] int 64 (0th int of runArray)
 //  0,0,0,0,0,0,1,0  int 2 (7th int of runArray)
 //  0,0,0,0,0,0,0,1 63->56 int 1 (6th int of runArray)

 //6 0,1,0,0,0,0,0,0 [2 IS PERM ON] int 64 (0th int of runArray)
 //  0,0,0,0,0,0,0,1 56 int 1 (7th int of runArray)

 //7 0,1,0,0,0,0,0,0 [2 IS PERM ON] int 64 (0th int of runArray)
 //  0,0,0,1,0,0,0,1 56->52 int 17 (6th int of runArray)

 //8 0,0,0,1,0,0,0,0 52 int 16 (6th int of runArray)

 // this is basically how I was tracing through the time steps
 // for moving droplets. 8 steps were required to take the droplet
 // from the rezervoir the pad. notice how from the first time step
 // the HVOUT2 pad is going to be kept on. Also notice how from 
 // each time-step, you can see we use the methods of moving
 // droplets by keeping the previous pad on as it spreads to the
 // next. Look at time steps 1 to 3, this is where we are having liquid
 // initially on the rez, the it spreads to rez + bridge, then spreads
 // rez + bridge + PAD25, then we turn off the bridge. This means,
 // at the end of step 3 we have the rez with a droplet, and PAD25 with
 // a droplet. Notice how the pattern was carryed out with bits.
 // {0 1 0 0 0 0 0 0 - > 1 1 0 0 0 0 0 0} this is how we spread the
 // droplets from rez then rez+bridge. This movement 
 // (again time-steps 0 to 1) will have runArray 0 and 1 equal to
 // [64,0,0,0,0,0,0,0] and [192,0,0,0,0,0,0,0] respectively.

 // END OF DEMO 8 STEPS THROUGH

 // 0,0,0,1,0,0,0,0 int 16
 // 0,0,0,1,0,0,0,0 52->60 int 16

 // 0,0,0,1,0,0,0,0 60 int 16

 // 0,0,0,1,0,0,0,0 int 16
 // 0,0,1,0,0,0,0,0 60->11 int 32

 // 0,0,1,0,0,0,0,0 11 int 32

 // 0,0,1,1,0,0,0,0 11->12

 // 0,0,0,1,0,0,0,0 12

 // INFORMATION FOR PAD DIRECTION

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

  digitalWrite(LAT, 0);

  digitalWrite(DIR, 0);

  digitalWrite(POL, 1);

  digitalWrite(BLANK, 1);

  // below not required for multiple HV507 use
  
  Serial.begin(9600);
  
  pinMode(pause, INPUT);

  pinMode(HOLDHIGH, OUTPUT);

  digitalWrite(HOLDHIGH, 1);

}

void loop (){

    // repeat the run count (in this instance 0-7 8 total)
    // possible to add reversing code to bring droplet 
    // back to rezervoir so you can prevent having to remove
    // ITO glass.
    
    for(runNum=0; runNum<runCount; runNum++){

    // Serial.print used for debugging purposes,
    // monitor on laptop Serial Monitor

    Serial.print("Sending run: ");
    Serial.println(runNum+1);

    delay(750);

    // disable latch while writing to HV507
    
    // this is exactly where the danger of using uC
    // for delivery of data, FPGA come in handy here
    // not only for parallelizing, but just larger
    // pad count designs. many concurrent HV507 or
    // many chained HV507, need to answer...
    // STM32 may come to save the day with 150+ MHz.

    // if we are chaining together HV507, running DoutB1
    // into DoutA2 then DoutB2 into DoutA3 and so on, this
    // means either we have to *individually* enable and 
    // disable latch pins, which I think is the rub...
    
    digitalWrite(LAT, 1); 
    
    for(i = 0; i<width; i++){

      // this is the basic output using shiftOut which will only
      // output 8 bit values at a time.
      
      shiftOut(DATA, CLK, LSBFIRST, runArray[(runCount-1)-runNum][i]);

    }

    digitalWrite(LAT, 1);

    // using the button as a blocking mechanism
    // passing a button press will continue to 
    // the next time step 
    
    while(digitalRead(pause));
    
    }
    
}
