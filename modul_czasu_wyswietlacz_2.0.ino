#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h> //Dołączenie bilbioteki wyswietlacza

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza

unsigned long aktualnyCzas=0;
unsigned long zapamietanyCzas = 0;
unsigned long roznicaCzasu = 0;
void setup() {
  //Wyswietlacz
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print(""); //Wyświetlenie tekstu
  lcd.setCursor(0, 1); //Ustawienie kursora
  lcd.print(""); //Wyświetlenie tekstu

  //Zegar
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");
}
 
void loop() {
  WyswietlGodzine();
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.print('0');
  }
  lcd.print(number);
}
void zamianaMiesiaca(int miesiac)
{
  //lcd.setCursor(0, 1); //Ustawienie kursor
  if(miesiac == 1)
  lcd.print("Styczen");
  else if(miesiac ==2)
  lcd.print("Luty");
  else if(miesiac ==3)
  lcd.print("Marzec");
  else if(miesiac==4)
  lcd.print("Kwiecien");
  else if (miesiac==5)
  lcd.print("Maj");
  else if(miesiac==6)
  lcd.print("Czerwiec");
  else if(miesiac==7)
  lcd.print("Lipiec");
  else if(miesiac==8)
  lcd.print("Sierpien");
  else if(miesiac==9)
  lcd.print("Wrzesien");
  else if(miesiac==10)
  lcd.print("Pazdziernik");
  else if(miesiac==11)
  lcd.print("Listopad");
  else if(miesiac==12)
  lcd.print("Grudzien");

}
void Godzina()
{
    tmElements_t tm;
  if (RTC.read(tm)) {
    lcd.setCursor(0, 0); //Ustawienie kursora
    print2digits(tm.Hour);
    lcd.print(':');
    print2digits(tm.Minute);
    lcd.print(':');
    print2digits(tm.Second);

    lcd.setCursor(0, 1); //Ustawienie kursor
    lcd.print(tm.Day);
    lcd.print(' ');
    zamianaMiesiaca(tm.Month);
    lcd.write(' ');
    lcd.print(tmYearToCalendar(tm.Year));
    //Serial.println();
  } else {
    if (RTC.chipPresent()) {
      lcd.println("Run the SetTime");
    } else {
      lcd.println("DS1307 read error!");
      lcd.println();
    }
    delay(9000);
  }
  //delay(1000);
}
void WyswietlGodzine()
{
    aktualnyCzas=millis();
  roznicaCzasu = aktualnyCzas - zapamietanyCzas;
  if (roznicaCzasu >= 1000UL) {
    //Zapamietaj aktualny czas
    zapamietanyCzas = aktualnyCzas;
    //Wyslij do PC
    Serial.println(aktualnyCzas);
    Godzina();
  }
  }
