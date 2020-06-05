#Common Emitter Amplifier

#Parameters
Rb1 = 0
Rb2 = 0
Rc = 0
Re = 0
Rl = 5000   # Load Resistor
Beta = 170  # Beta of the BJT. Find it using your multimeter
Vt = 0.025  # 25mV
Vcc = 16    # DC Source
Vbe = 0.7   # Voltage drop across the diode from Base to Emitter
VA = 100    # Early Voltage
Ic = 0

#Calculations
Alpha = Beta/(Beta + 1)
print(Alpha)

# Resistor Array
ResisArray = []

# Parallel Resistor Calc
def para(firstR, secondR):
  return (firstR * secondR)/(firstR + secondR)

for x in range(1200, 3000, 1):   # range(starting num, ending num -1, increment) all integers
  Vb = x *0.001
  Ve = Vb - Vbe

  for Re in range(100, 5000, 50):
    Ie = Ve / Re;
    Ic = Ie * Alpha

    for Rc in range(100, 10000, 50):
      Vc = Vcc - Rc * Ic;
      Vce = Vc-Ve

      # ACLL
      VcetMAX = (para(Rc, Rl) * Ic + Vce)

      if( (VcetMAX - Vce) < Vce):
        VSwing = (VcetMAX - Vce) *2
      else:
        VSwing = Vce *2

      if( (Vce > 6) and (Vce < 8) ):
        Rpi = Beta * Vt / Ic
        Ro = VA / Ic
        Gain = - para( para(Rc, Rl), Ro) * (1/Rpi) * Beta

        if(Gain < -280):
          #Qpoint = (Vce, Ic)
          print(Gain)
          #print("Qpoint: ", Qpoint)
          ResisArray.append([Rc, Re, Vb])
          print("Re:", Re, "Rc:", Rc, "Vb:", Vb, " VSwing: ", VSwing)

print(para(10, 20))