#include <LiquidCrystal.h>
#include <IRremote.hpp>

uint8_t CURSOR_POSITION = 0;
bool isEnd = false;
const uint8_t RS = 13, EN = 12, D4 = 11, D5 = 10, D6 = 9, D7 = 8;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
//IRrecv irrecv(2);
//decode_results results;

String str;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("=Calc=  | ");
  lcd.setCursor(0, 1);
  lcd.cursor();
  IrReceiver.begin(2, ENABLE_LED_FEEDBACK);
}

void clearLCDLine(int line)
{               
  lcd.setCursor(0,line);
  for(int n = 0; n < 16; n++)
    lcd.print(" ");
  lcd.setCursor(0,line);
}

void addChar(String &str, char c)
{
  str = str.substring(0, CURSOR_POSITION) + c + str.substring(CURSOR_POSITION, str.length());
}

int getFirstValue(String str)
{
  String tmpStr;
  for(auto &it : str)
    if(it != '+' && it != '-' && it != '=')
      tmpStr += it;
    else
      break;
  return tmpStr.toInt();
}

int getExpression(String str)
{
  int x = getFirstValue(str);

  for(auto &it : str)
  {
    Serial.println(it);
    if(it == '+' || it == '-' || it == '=')
    {
      switch(it)
      {
        case '+':
          x += getFirstValue(str.substring(str.indexOf('+')+1, str.length()));
          str = str.substring(str.indexOf('+')+1, str.length());
          break;
        case '-':
          x -= getFirstValue(str.substring(str.indexOf('-')+1, str.length()));
          str = str.substring(str.indexOf('-')+1, str.length());
          break;
        case '=':
          return x;
          break;
      }
    }

  }
  return x;
}

void loop() {
  if (IrReceiver.decode()) 
  {
    //Serial.println(IrReceiver.decodedIRData.command);
    switch(IrReceiver.decodedIRData.command)
    {
      case 22: // 0
        if(!isEnd)
        {
          addChar(str, '0');
          CURSOR_POSITION++;
          delay(500);
        }
        break;
      case 12:  // 1
        if(!isEnd)
        {
          addChar(str, '1');
          CURSOR_POSITION++;
          delay(500);
        }
        break; 
      case 24: // 2
        if(!isEnd)
        {
          addChar(str, '2');
          CURSOR_POSITION++;
          delay(500);
        }
        break;
      case 94: // 3
        if(!isEnd)
        {
          addChar(str, '3');
          CURSOR_POSITION++;
          delay(500);
        }
        break;
      case 8:  // 4
        if(!isEnd)
        {
          addChar(str, '4');
          CURSOR_POSITION++;
          delay(500);
        }
        break;
      case 28: // 5
        if(!isEnd)
        {
          addChar(str, '5');
          CURSOR_POSITION++;
          delay(500);
        }
        break;
      case 90: // 6
        if(!isEnd)
        {
          addChar(str, '6');
          CURSOR_POSITION++;
          delay(500);
        }
        break;
      case 66: // 7
        if(!isEnd)
        {
          addChar(str, '7');
          CURSOR_POSITION++;
          delay(500);
        }
        break;
      case 82: // 8
        if(!isEnd)
        {
          addChar(str, '8');
          CURSOR_POSITION++;
          delay(500);
        }
        break;
      case 74: // 9
        if(!isEnd)
        {
          addChar(str, '9');
          CURSOR_POSITION++;
          delay(500);
        }
        break;
      case 21: // +
        if(str[CURSOR_POSITION-1] != '+' && str[CURSOR_POSITION-1] != '-' && str[CURSOR_POSITION-1] != '=' && !isEnd)
        {
          addChar(str, '+');
          CURSOR_POSITION++;
        }
        break;
      case 7:  // -
        if(str[CURSOR_POSITION-1] != '+' && str[CURSOR_POSITION-1] != '-' && str[CURSOR_POSITION-1] != '=' && !isEnd)
        {
          addChar(str, '-');
          CURSOR_POSITION++;
        }
        break;
      case 67:  // =
        if(str[CURSOR_POSITION-1] != '+' && str[CURSOR_POSITION-1] != '-' && str[CURSOR_POSITION-1] != '=' && !isEnd)
        {
          addChar(str, '=');
          str += getExpression(str);
          CURSOR_POSITION++;
          isEnd = true;
        }
        break;
      case 9:  // delCur
        if(!isEnd)
        {
          str.remove(CURSOR_POSITION-1);
          delay(500);
        }
        break;
      case 70:  // delAll
        CURSOR_POSITION = 0;
        str.remove(0, str.length());
        Serial.println(str);
        isEnd = false;
        delay(500);
        break;
      case 68:  // --
        if(!isEnd)
        {
          CURSOR_POSITION--;
          delay(500);
        }
        break;
      case 64:  // ++
        if(!isEnd)
        {
          CURSOR_POSITION++;
          delay(500);
        }
        break;
      default:
        Serial.println("Unknown");
        break;
    }

    IrReceiver.resume(); 
    IrReceiver.stop();
    lcd.setCursor(10, 0);
    lcd.print(str[str.length()-1]);
    clearLCDLine(1);
    lcd.print(str);
    lcd.setCursor(CURSOR_POSITION, 1);
    delay(10);
    IrReceiver.start(10000);
  }
}
