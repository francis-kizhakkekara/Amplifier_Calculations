// Mosfet Common Source Amplifier
#include <iostream>
#include <cmath>
using namespace std;

double para(double Resistor1, double Resistor2);

int main() {  

  // Initialize
  // Constants and constraints
  double VA, VT, VDD, kn, RL;
  VA = 200.0;               // Volts
  VT = 1.4;                 // Volts
  kn = 600 * pow(10.0, -6); // 600 uA/(V^2)
  VDD = 15.0;               // Volts
  RL = 20000.0;             // Ohms

  // Parameters
  double R1, R2, RS, RD, Ro, Rgain, VDS; 
  double R1p, R2p, RSp, RDp;  
  R1p = 180000;
  R2p = 82000;
  RDp = 50000;
  RSp = 50000;
  VDS = 7.2;          // Q point voltage

  // Other values
  double VG, VS, VGS;
  VG = 0;
  VS = 0;
  VGS = 0;
  Rgain = 0;    
  
  double IDSQ, SQRTpos, VGSeqn, errPcnt, gm, GAIN = 0;

  // VGS = sqrt(IDS / (0.5 * kn * (1 + VDS/VA)) + VT;
  for(R1 = R1p; R1 > 100; R1 = R1 - 500){
    for(R2 = R2p; R2 > 100; R2 = R2 - 100){
      for(RD = RDp; RD > 50; RD = RD - 100){
        for(RS = RSp; RS > 50; RS = RS - 500){

          // Q point current VGS using ID formula
          IDSQ = (VDD - VDS) / (RD + RS);
          // VGS using ID formula
          VGSeqn = sqrt(IDSQ / (0.5 * kn * (1 + VDS/VA)) ) + VT;         

          // finding the VGS from Resistors
          VS = IDSQ * RS;
          VG = (VDD * R2) / (R1 + R2);
          VGS = VG - VS;          
          
          errPcnt = 100.0 * abs(VGS-VGSeqn)/VGSeqn;

          if(errPcnt < 2){
            gm = 2 * IDSQ / (VGSeqn - VT);
            Ro = VA / IDSQ;
            Rgain = para( para(RD, RL), Ro );
            GAIN = -1 * gm  * Rgain;

            if(GAIN < -6.5 && VG > 3.2){
              cout << GAIN << " " << R1 << " " << R2 << " " << RD << " " << RS << " IDS" << IDSQ 
              << " VG" << VG << endl;
            }            
            
          }
        }        
      }      
    }
  }

  cout << "ended " << endl;
}

double para(double Resistor1, double Resistor2){
  return (Resistor1 * Resistor2) / (Resistor1 + Resistor2);
}