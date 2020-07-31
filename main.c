#include "mbed.h"
#include "Servo.h"
#include "MFRC522.h"
#include "Motor.h"

Serial pc(USBTX, USBRX); // tx, rx
Serial bt(PTC15,PTC14);
DigitalOut LedRed   (LED_RED);
DigitalOut LedGreen (LED_GREEN);
DigitalOut LedBlue  (LED_BLUE);
Motor m1(D5, D8, D7);
Motor m2(D6, D4, D2);
Servo servo(D3);
MFRC522    RfChip   (PTD2, PTD3, PTD1, PTE25, PTD0);

//global variable lidState, initialize to closed
enum CoolerLid {
  OPENED,
  CLOSED
};

CoolerLid lidState = CLOSED;

char tagID;
int blueTag = 207;
int whiteTag = 247;

void lidMove(void)
{
    pc.printf("\nLid open/close triggered\n\r");
    
    switch (lidState) 
    {
    case OPENED:
      pc.printf("Access Granted! Lid will now close.\n\n\r");
      servo = 1.0;
      lidState = CLOSED;
      break;
    case CLOSED:
      pc.printf("Access Granted! Lid will now open.\n\n\r");
      servo = 0.0;
      lidState = OPENED;
      break;
    }
}

bool cardRead(void)
{
    
    //check for new card
    if ( ! RfChip.PICC_IsNewCardPresent())
    {   
        return false;
    }

    // Select one of the cards
    if ( ! RfChip.PICC_ReadCardSerial())
    {
        return false;
    }
        
    pc.printf("RFID Detected\n\r");
    
    tagID = '\0';
    
    // Print Card UID
    pc.printf("Card UID: ");
        
    for (uint8_t i = 0; i < RfChip.uid.size; i++)
    {
        pc.printf(" %X02", RfChip.uid.uidByte[i]);
    }
    
    for (uint8_t i = 0; i < RfChip.uid.size; i++)
    {
        tagID= RfChip.uid.uidByte[i]+ tagID;
    }
        
    pc.printf("\n\rCard Tag ID: %d\n\r",tagID);
    wait_ms(1000);
    return true;
    
}

void motorsForward(void)
{ 
       m1.speed(-0.5); 
       m2.speed(-0.5);
}    

void stopMotors(void)
{
    m1.speed(0);
    m2.speed(0);
}

void motorsBack(void)
{ 
       m1.speed(0.5); 
       m2.speed(0.5);
}   

void motorsR(void)
{ 
       m1.speed(-0.5); 
       m2.speed(0);
}  

void motorsL(void)
{ 
       m1.speed(0); 
       m2.speed(-0.5);
}  

int main() 
{ 
    pc.printf("\r=====Start Motorized Cooler Program =====\n\n\r");
    
    //Initialize RFID Reader
    RfChip.PCD_Init();
    
    //Close Cooler Lid if Not Closed
    servo = 1.0;
    
    while(1)
    {
        LedGreen = 0;
        LedBlue = 1;
        LedRed = 1;
        
        // Look for new RFID card
        if(cardRead())
        {
            //check uid
            if(tagID == blueTag || tagID == whiteTag)
            {   LedBlue = 0;
                LedGreen = 1;
                LedRed = 1;
                wait_ms(200);
                //call lidMove function if there is a match
                lidMove(); 
            }
            else
            {
                LedRed = 0;
                LedGreen = 1; 
                LedBlue = 1;
                printf("Access Denied. Card Unrecognized.\n\r");
                wait_ms(200);
            }
        }//if(cardRead())
        
        //interface with app: check for kill switch, print current gps data
        if(bt.readable())
        {
            switch(bt.getc())
           {
                case(0): //off
                {
                    //get out of while loop and wait for switch to press again??
                    LedRed = 0;
                    LedGreen = 1;
                    LedBlue = 1;
                    pc.printf("Motors turning off.\n\r");
                    stopMotors();
                    break;
                }
            
                case(1): //move forward
                {
                    pc.printf("Moving forward...\n\r");
                    motorsForward();
                    break;
                }
                
                case(2): //move backward
                {
                    pc.printf("Moving backward...\n\r");
                    motorsBack();
                    break;
                }
                
                case(3): //move right
                {
                    pc.printf("Moving right...\n\r");
                    motorsR();
                    break;
                }
                
                case(4): //move left
                {
                    pc.printf("Moving left...\n\r");
                    motorsL();
                    break;
                }
                
            }//switch
            
        }//if(bt.readable())
        
    }//while(1)

}//main

