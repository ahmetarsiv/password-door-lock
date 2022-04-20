#include <Servo.h>
#include <LiquidCrystal.h>      
#include <Keypad.h>


LiquidCrystal lcd(13,12, 11, 10, 9, 8);

const byte satirSayisi= 4; 
const byte sutunSayisi= 4;



char tuslar[satirSayisi][sutunSayisi]=
{
{'1', '2', '3', 'A'}, // 1. Satır karakterleri 
{'4', '5', '6', 'B'}, // 2. Satır karakterleri
{'7', '8', '9', 'C'}, // 3. Satır karakterleri
{'*', '0', '#', 'D'}  // 4. Satır karakterleri
};
byte satirPinleri[satirSayisi] = {2,3,4,5}; 

// Satır pinlerimizi taımlıyoruz. byte 0 ile 255 arası
byte sutunPinleri[sutunSayisi]= {A3,A2,A0,A1};  

// Sütun pinlerimizi tanımlıyoruz

Keypad tusTakimi= Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, satirSayisi, sutunSayisi);

// tustakimi isminde bir keypad oluşturduk
// map harita oluşturuyoruz


Servo servo;

String girilensifre = "";
String sifre = "D";

/* string(dizi) birden fazla karakteri
hafızada tutmaya yarayan bir değişken tipidir. 
String parçalama, birleştrime, istenilen harfi 
bulma/silme/değiştirme gibi özellikler sıkça 
kullanılmaktadır. */

void setup()
{  

  lcd.begin(16, 2);
  lcd.print("Lcd Calisiyor");
  delay(100);
  lcd.clear();
  servo.attach(7);
  servo.write(0);
}

void loop()
{
    char tus = tusTakimi.getKey();
    if (tus != NO_KEY)
    {
          switch(tus)
        {
            case '*':
                  lcd.clear();
                  girilensifre="";
                  servo.write(0);
                  lcd.setCursor(0,1);
                  lcd.write("Kilitleniyor");
                  delay(100);
                  lcd.clear();
                  break;
              
             case '#':
                  lcd.setCursor(0,1);
                 
                  if(girilensifre==sifre) {
                    servo.write(90);
                    lcd.write("Kilit Acik");
                  }
                else
                {
                      lcd.write("Gecersiz");                  
                }
                  delay(100);
                lcd.clear();
                  girilensifre="";
                  break;
              default: // hiç bir case değeri yoksa işletilir
                  lcd.write(tus);
                  girilensifre+=tus;
                  break;
        }
    }
}
