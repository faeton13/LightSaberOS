/*
 * Light.cpp
 *
 * author: 		Sebastien CAPOU (neskweek@gmail.com)
 * Source : 	https://github.com/neskweek/LightSaberOS
 */
#include "Light.h"
#include "Config.h"

#if defined NEOPIXEL
#include <WS2812.h>
#endif

// ====================================================================================
// ===              	    			LED FUNCTIONS		                		===
// ====================================================================================
#if defined LEDSTRINGS

static uint8_t flickerPos = 0;
static long lastFlicker = millis();

void lightOn(uint8_t ledPins[], int8_t segment) {
// Light On

	if (segment == -1) {
		for (uint8_t i = 0; i < 6; i++) {
			digitalWrite(ledPins[i], HIGH);
		}
	} else {
		digitalWrite(ledPins[segment], HIGH);
	}
	/* Should have save some hex size
	 * Needs further testing
	 switch (segment) {
	 case -1: // Light up everything at once !
	 PORTD |= B01101000;
	 PORTB |= B00001110;
	 break;
	 case 0:
	 PORTD |= (1 << PD3);//DPIN 3
	 break;
	 case 1:
	 PORTD |= (1 << PD5);//DPIN 5
	 break;
	 case 2:
	 PORTD |= (1 << PD6);//DPIN 6
	 break;
	 case 3:
	 PORTB |= (1 << PD1);//DPIN 9
	 break;
	 case 4:
	 PORTB |= (1 << PD2);//DPIN 10
	 break;
	 case 5:
	 PORTB |= (1 << PD3);//DPIN 11
	 break;
	 }
	 */
} //lightOn

void lightOff() {
// shut Off
	//Shut down PWM
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0B1));
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1B1));
	TCCR2A &= ~((1 << COM2A1) | (1 << COM2B1));
	//Shut down everything at once
	PORTB &= B11010001;
	PORTD &= B10010111;
} //lightOff

void lightIgnition(uint8_t ledPins[], uint16_t time, uint8_t type) {

	switch (type) {
		case 0:
// Light up the ledstrings Movie-like
		for (uint8_t i = 0; i < 6; i++) {
			digitalWrite(ledPins[i], HIGH);
			delay(time / 5);
		}
		/*
		 PORTD |= (1 << PD3);//DPIN 3
		 delay(time / 5);
		 PORTD |= (1 << PD5);//DPIN 5
		 delay(time / 5);
		 PORTD |= (1 << PD6);//DPIN 6
		 delay(time / 5);
		 PORTB |= (1 << PD1);//DPIN 9
		 delay(time / 5);
		 PORTB |= (1 << PD2);//DPIN 10
		 delay(time / 5);
		 PORTB |= (1 << PD3);//DPIN 11
		 */
		break;
		case 1:
		for (int8_t i = 5; i >= 0; i--) {
			for (uint8_t j = 0; j <= i; j++) {
				if (j > 0) {
					digitalWrite(ledPins[j - 1], LOW);
				}
				digitalWrite(ledPins[j], HIGH);
				delay(time / 20);
			}
		}
		/*
		 digitalWrite(ledPins[0], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[0], LOW);
		 digitalWrite(ledPins[1], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[1], LOW);
		 digitalWrite(ledPins[2], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[2], LOW);
		 digitalWrite(ledPins[3], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[3], LOW);
		 digitalWrite(ledPins[4], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[4], LOW);
		 digitalWrite(ledPins[5], HIGH);
		 delay(time / 20);

		 digitalWrite(ledPins[0], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[0], LOW);
		 digitalWrite(ledPins[1], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[1], LOW);
		 digitalWrite(ledPins[2], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[2], LOW);
		 digitalWrite(ledPins[3], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[3], LOW);
		 digitalWrite(ledPins[4], HIGH);
		 delay(time / 20);

		 digitalWrite(ledPins[0], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[0], LOW);
		 digitalWrite(ledPins[1], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[1], LOW);
		 digitalWrite(ledPins[2], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[2], LOW);
		 digitalWrite(ledPins[3], HIGH);
		 delay(time / 20);

		 digitalWrite(ledPins[0], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[0], LOW);
		 digitalWrite(ledPins[1], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[1], LOW);
		 digitalWrite(ledPins[2], HIGH);
		 delay(time / 20);

		 digitalWrite(ledPins[0], HIGH);
		 delay(time / 20);
		 digitalWrite(ledPins[0], LOW);
		 digitalWrite(ledPins[1], HIGH);
		 delay(time / 20);

		 digitalWrite(ledPins[0], HIGH);
		 // Light up the ledstrings invert
		 /*
		 PORTD |= (1 << PD3);
		 delay(time / 20);
		 PORTD &= ~(1 << PD3);
		 PORTD |= (1 << PD5);
		 delay(time / 20);
		 PORTD &= ~(1 << PD5);
		 PORTD |= (1 << PD6);
		 delay(time / 20);
		 PORTD &= ~(1 << PD6);
		 PORTB |= (1 << PD1);
		 delay(time / 20);
		 PORTB &= ~(1 << PD1);
		 PORTB |= (1 << PD2);
		 delay(time / 20);
		 PORTB &= ~(1 << PD1);
		 PORTB |= (1 << PD3);
		 delay(time / 20);

		 PORTD |= (1 << PD3);
		 delay(time / 20);
		 PORTD &= ~(1 << PD3);
		 PORTD |= (1 << PD5);
		 delay(time / 20);
		 PORTD &= ~(1 << PD5);
		 PORTD |= (1 << PD6);
		 delay(time / 20);
		 PORTD &= ~(1 << PD6);
		 PORTB |= (1 << PD1);
		 delay(time / 20);
		 PORTB &= ~(1 << PD1);
		 PORTB |= (1 << PD2);
		 delay(time / 20);

		 PORTD |= (1 << PD3);
		 delay(time / 20);
		 PORTD &= ~(1 << PD3);
		 PORTD |= (1 << PD5);
		 delay(time / 20);
		 PORTD &= ~(1 << PD5);
		 PORTD |= (1 << PD6);
		 delay(time / 20);
		 PORTD &= ~(1 << PD6);
		 PORTB |= (1 << PD1);
		 delay(time / 20);

		 PORTD |= (1 << PD3);
		 delay(time / 20);
		 PORTD &= ~(1 << PD3);
		 PORTD |= (1 << PD5);
		 delay(time / 20);
		 PORTD &= ~(1 << PD5);
		 PORTD |= (1 << PD6);
		 delay(time / 20);

		 PORTD |= (1 << PD3);
		 delay(time / 20);
		 PORTD &= ~(1 << PD3);
		 PORTD |= (1 << PD5);
		 delay(time / 20);

		 PORTD |= (1 << PD3);
		 */
		break;
	}
}				//lightIgnition

void lightRetract(uint8_t ledPins[], uint16_t time, uint8_t type) {
	/*
	 //Make sure the light will be on after PWM shut off
	 PORTB |= B00001110;
	 PORTD |= B01101000;
	 //Shut down PWM
	 TCCR0A &= ~((1 << COM0A1) | (1 << COM0B1));
	 TCCR1A &= ~((1 << COM1A1) | (1 << COM1B1));
	 TCCR2A &= ~((1 << COM2A1) | (1 << COM2B1));
	 */
	switch (type) {
		case 0:
// Light off the ledstrings Movie Like
		for (int8_t i = 5; i >= 0; i--) {
			//BUG CORRECTION:
			//Not uint8_t here because Arduino nano clones did go
			// on an infinite loop for no reason making the board
			// crash at some point.
			digitalWrite(ledPins[i], 0);
			delay(time / 5);
		}
		/*
		 //Shut down each Digital PIN
		 PORTB &= ~(1 << PD3);				//DPIN 11
		 delay(time / 5);
		 PORTB &= ~(1 << PD2);				//DPIN 10
		 delay(time / 5);
		 PORTB &= ~(1 << PD1);				//DPIN 9
		 delay(time / 5);
		 PORTD &= ~(1 << PD6);				//DPIN 6
		 delay(time / 5);
		 PORTD &= ~(1 << PD5);				//DPIN 5
		 delay(time / 5);
		 PORTD &= ~(1 << PD3);				//DPIN 3
		 */
		break;
		case 1:
// Light off the ledstrings invert
		for (int8_t i = 5; i >= 0; i--) {
			for (uint8_t j = 0; j <= i; j++) {
				if (j > 0) {
					digitalWrite(ledPins[j - 1], HIGH);
				}
				digitalWrite(ledPins[j], LOW);
				delay(time / 20);
			}
		}
		/*
		 PORTD &= ~(1 << PD3);
		 delay(time / 20);

		 PORTD &= ~(1 << PD5);
		 PORTD |= (1 << PD3);
		 delay(time / 20);
		 PORTD &= ~(1 << PD3);
		 delay(time / 20);

		 PORTD &= ~(1 << PD6);
		 PORTD |= (1 << PD5);
		 delay(time / 20);
		 PORTD &= ~(1 << PD5);
		 PORTD |= (1 << PD3);
		 delay(time / 20);
		 PORTD &= ~(1 << PD3);
		 delay(time / 20);

		 PORTB &= ~(1 << PD1);
		 PORTD |= (1 << PD6);
		 delay(time / 20);
		 PORTD &= ~(1 << PD6);
		 PORTD |= (1 << PD5);
		 delay(time / 20);
		 PORTD &= ~(1 << PD5);
		 PORTD |= (1 << PD3);
		 delay(time / 20);
		 PORTD &= ~(1 << PD3);
		 delay(time / 20);

		 PORTB &= ~(1 << PD2);
		 PORTB |= (1 << PD1);
		 delay(time / 20);
		 PORTB &= ~(1 << PD1);
		 PORTD |= (1 << PD6);
		 delay(time / 20);
		 PORTD &= ~(1 << PD6);
		 PORTD |= (1 << PD5);
		 delay(time / 20);
		 PORTD &= ~(1 << PD5);
		 PORTD |= (1 << PD3);
		 delay(time / 20);
		 PORTD &= ~(1 << PD3);
		 delay(time / 20);

		 PORTB &= ~(1 << PD3);
		 PORTB |= (1 << PD2);
		 delay(time / 20);
		 PORTB &= ~(1 << PD2);
		 PORTB |= (1 << PD1);
		 delay(time / 20);
		 PORTB &= ~(1 << PD1);
		 PORTD |= (1 << PD6);
		 delay(time / 20);
		 PORTD &= ~(1 << PD6);
		 PORTD |= (1 << PD5);
		 delay(time / 20);
		 PORTD &= ~(1 << PD5);
		 PORTD |= (1 << PD3);
		 delay(time / 20);
		 PORTD &= ~(1 << PD3);



		 */
		break;
	}
}				//lightRetract

#if defined FoCSTRING
void FoCOn(uint8_t pin) {
	digitalWrite(FoCSTRING, HIGH);
//	PORTC &= ~(1 << PD3);

} //FoCOn
void FoCOff(uint8_t pin) {
	digitalWrite(FoCSTRING, LOW);
//	PORTC |= (1 << PD3);
} //FoCOff
#endif

void lightFlicker(uint8_t ledPins[], uint8_t type, uint8_t value) {
	uint8_t variation = abs(analogRead(SPK1) - analogRead(SPK2));
	uint8_t brightness;
	if (not value) {
// Calculation of the amount of brightness to fade
		brightness = MAX_BRIGHTNESS - variation;
	} else {
		brightness = value;
	}
#if defined LS_HEAVY_DEBUG
	Serial.print(F("Brightness: "));
	Serial.print(brightness);
	Serial.print(F("   SPK1: "));
	Serial.print(analogRead(SPK1));
	Serial.print(F("   SPK2: "));
	Serial.println(analogRead(SPK2));
#endif

	switch (type) {
		case 0:
		// std Flickering
		for (uint8_t i = 0; i <= 5; i++) {
			analogWrite(ledPins[i], brightness);
		}
		break;
		case 1:
		// pulse Flickering
		for (uint8_t i = 0; i <= 5; i++) {
			if (i != flickerPos)
			analogWrite(ledPins[i], brightness - variation / 2);
			else
			analogWrite(ledPins[i], MAX_BRIGHTNESS);
		}
		if ((flickerPos != 0
				and millis() - lastFlicker > (120 - (100 - 15 * flickerPos)))
				or (flickerPos == 0 and millis() - lastFlicker > 300)) {
			flickerPos++;
			lastFlicker = millis();
			if (flickerPos == 6) {
				flickerPos = 0;
			}
		}
		break;
		case 2:
		// anarchic Flickering
		for (uint8_t i = 0; i <= 5; i++) {
			randomSeed(analogRead(ledPins[i]));
			analogWrite(ledPins[i],
			MAX_BRIGHTNESS - random(variation, variation * 2));
		}
		break;
	}
} //lightFlicker

#endif
#if defined LUXEON

void lightOn(uint8_t ledPins[], uint8_t color[]) {
// Light On
	for (uint8_t i = 0; i <= 2; i++) {
		analogWrite(ledPins[i], MAX_BRIGHTNESS * color[i] / rgbFactor);
	}
} //lightOn

void lightOff(uint8_t ledPins[]) {
// shut Off
	for (uint8_t i = 0; i <= 2; i++) {
		analogWrite(ledPins[i], LOW);
	}
} //lightOff

void lightIgnition(uint8_t ledPins[], uint8_t color[], uint16_t time) {

// Fade in to Maximum brightness
	for (uint8_t fadeIn = 255; fadeIn > 0; fadeIn--) {
		for (uint8_t i = 0; i <= 2; i++) {
			analogWrite(ledPins[i],
					(MAX_BRIGHTNESS / fadeIn) * color[i] / rgbFactor);
		}
		delay(time / 255);
	}
} //lightIgnition

void lightRetract(uint8_t ledPins[], uint8_t color[], uint16_t time) {
// Fade out

	for (uint8_t fadeOut = 1; fadeOut < 255; fadeOut++) {
		for (uint8_t i = 0; i <= 2; i++) {
			analogWrite(ledPins[i],
					(MAX_BRIGHTNESS / fadeOut) * color[i] / rgbFactor);
		}
		delay(time / 255);
	}

	lightOff(ledPins);
} //lightRetract

void lightFlicker(uint8_t ledPins[], uint8_t color[], uint8_t value) {
	uint8_t brightness;
	if (not value) {
// Calculation of the amount of brightness to fade
		brightness = MAX_BRIGHTNESS
		- (abs(analogRead(SPK1) - analogRead(SPK2)));
	} else {
		brightness = value;
	}
#if defined LS_HEAVY_DEBUG
	Serial.print(F("Brightness: "));
	Serial.print(brightness);
	Serial.print(F("   SPK1: "));
	Serial.print(analogRead(SPK1));
	Serial.print(F("   SPK2: "));
	Serial.println(analogRead(SPK2));
#endif
	for (uint8_t i = 0; i <= 2; i++) {
		analogWrite(ledPins[i], brightness * color[i] / rgbFactor);
	}
} //lightFlicker

#if defined MY_OWN_COLORS
void getColor(uint8_t color[], uint8_t colorID) {
	color[3] = colorID;
	switch (colorID) {
		case 0:
//Red
		color[0] = 100;
		color[1] = 0;
		color[2] = 0;
		break;
		case 1:
//Green
		color[0] = 0;
		color[1] = 100;
		color[2] = 0;
		break;
		case 2:
//Blue
		color[0] = 0;
		color[1] = 0;
		color[2] = 100;
		break;
		default:
// White?
		color[0] = 100;
		color[1] = 100;
		color[2] = 100;
		break;
	}
} //getColor
#else
void getColor(uint8_t color[], uint16_t colorID) {
	uint8_t tint = (COLORS / 6);
	uint8_t step = rgbFactor / tint;
	color[3] = colorID;
	if ((colorID >= 0) and (colorID < (1 * tint))) {
//From Red to Yellow
		color[0] = 100;
		color[1] = step * (colorID % tint);
		color[2] = 0;
	} else if ((colorID >= (1 * tint)) and (colorID < (2 * tint))) {
// From Yellow to Green
		color[0] = 100 - (step * (colorID % tint));
		color[1] = 100;
		color[2] = 0;
	} else if ((colorID >= (2 * tint)) and (colorID < (3 * tint))) {
// From Green to Aqua
		color[0] = 0;
		color[1] = 100;
		color[2] = step * (colorID % tint);
	} else if ((colorID >= (3 * tint)) and (colorID < (4 * tint))) {
// From Aqua to Blue
		color[0] = 0;
		color[1] = 100 - (step * (colorID % tint));
		color[2] = 100;
	} else if ((colorID >= (4 * tint)) and (colorID < (5 * tint))) {
// From Blue to Purple/Pink
		color[0] = step * (colorID % tint);
		color[1] = 0;
		color[2] = 100;
	} else if (colorID >= (5 * tint)) {
// From Purple/Pink to Red
		color[0] = 100;
		color[1] = 0;
		color[2] = 100 - (step * (colorID % tint));
	}

} //getColor
#endif
#endif

#if defined NEOPIXEL
static uint8_t flickerPos = 0;
static long lastFlicker = millis();
extern WS2812 pixels;
extern bool isFlickering;

extern cRGB currentColor;

void lightOn(cRGB color, int16_t pixel) {
	// Light On
	isFlickering = true;
	if (pixel == -1) {
		for (uint8_t i = 0; i < NUMPIXELS; i++) {
			pixels.set_crgb_at(i, color);
		}
	} else {
		pixels.set_crgb_at(pixel, color);
	}
	pixels.sync();
	isFlickering = false;
} //lightOn

void lightOff() {
// shut Off
	isFlickering = true;
	cRGB value;
	value.b = 0;
	value.g = 0;
	value.r = 0; // RGB Value -> Off
	for (uint8_t i = 0; i < NUMPIXELS; i++) {
		pixels.set_crgb_at(i, value);
	}
	pixels.sync();
	isFlickering = false;
} //lightOff

void lightIgnition(cRGB color, uint16_t time, uint8_t type) {
	cRGB value;
	value.r = MAX_BRIGHTNESS * color.r / rgbFactor;
	value.g = MAX_BRIGHTNESS * color.g / rgbFactor;
	value.b = MAX_BRIGHTNESS * color.b / rgbFactor;
	switch (type) {
	case 0:
// Light up the ledstrings Movie-like
		for (uint8_t i = 0; i < NUMPIXELS; i++) {
			pixels.set_crgb_at(i, value);
			i++;
			pixels.set_crgb_at(i, value);
			pixels.sync();
			delayMicroseconds(time * 1000 / (NUMPIXELS / 2));
		}
		//Serial.println(pixels.getBrightness());
		break;
		/*
		 case 1:
		 for (int8_t i = 5; i >= 0; i--) {
		 for (uint8_t j = 0; j <= i; j++) {
		 if (j > 0) {
		 digitalWrite(ledPins[j - 1], LOW);
		 }
		 digitalWrite(ledPins[j], HIGH);
		 delay(time / 20);
		 }
		 }
		 break;
		 */
	}
}				//lightIgnition

void lightRetract(uint16_t time, uint8_t type) {
	switch (type) {
	case 0:
		// Light off the ledstrings Movie Like
		cRGB value;
		value.b = 0;
		value.g = 0;
		value.r = 0; // RGB Value -> Off
		for (uint8_t i = NUMPIXELS; i > 0; i--) {
			//BUG CORRECTION:
			//Not uint8_t here because Arduino nano clones did go
			// on an infinite loop for no reason making the board
			// crash at some point.
			pixels.set_crgb_at(i, value);
			i--;
			pixels.set_crgb_at(i, value);
			pixels.sync();
			delayMicroseconds(time * 1000 / (NUMPIXELS / 2));
		}
		pixels.set_crgb_at(0, value);
		pixels.sync();
		break;
		/*
		 case 1:
		 // Light off the ledstrings invert
		 for (int8_t i = 5; i >= 0; i--) {
		 for (uint8_t j = 0; j <= i; j++) {
		 if (j > 0) {
		 digitalWrite(ledPins[j - 1], HIGH);
		 }
		 digitalWrite(ledPins[j], LOW);
		 delay(time / 20);
		 }
		 }
		 break;
		 */
	}
}				//lightRetract

void lightBlasterEffect(uint8_t pixel, uint8_t range) {
	isFlickering = true;
	for (uint8_t i = (pixel - 5 * range); i < (pixel + 5 * range); i++) {
		pixels.set_crgb_at(i, currentColor);
	}
	pixels.sync();
	isFlickering = false;
}

void lightFlicker(uint8_t value) {
	isFlickering = true;
	uint8_t variation = abs(analogRead(SPK1) - analogRead(SPK2));
	uint8_t brightness;
	if (not value) {
		// Calculation of the amount of brightness to fade
		brightness = MAX_BRIGHTNESS - variation;
	} else {
		brightness = value;
	}
#if defined LS_HEAVY_DEBUG
	Serial.print(F("Brightness: "));
	Serial.print(brightness);
	Serial.print(F("   SPK1: "));
	Serial.print(analogRead(SPK1));
	Serial.print(F("   SPK2: "));
	Serial.println(analogRead(SPK2));
#endif

//	switch (type) {
//	case 0:
	// std Flickering

	cRGB color;
	color.r = brightness * currentColor.r / rgbFactor;
	color.g = brightness * currentColor.g / rgbFactor;
	color.b = brightness * currentColor.b / rgbFactor;
	for (uint8_t i = 0; i <= NUMPIXELS; i++) {
		pixels.set_crgb_at(i, color);
	}
	pixels.sync();

//		break;
	/*
	 case 1:
	 // pulse Flickering
	 for (uint8_t i = 0; i <= 5; i++) {
	 if (i != flickerPos)
	 analogWrite(ledPins[i], brightness - variation / 2);
	 else
	 analogWrite(ledPins[i], MAX_BRIGHTNESS);
	 }
	 if ((flickerPos != 0
	 and millis() - lastFlicker > (120 - (100 - 15 * flickerPos)))
	 or (flickerPos == 0 and millis() - lastFlicker > 300)) {
	 flickerPos++;
	 lastFlicker = millis();
	 if (flickerPos == 6) {
	 flickerPos = 0;
	 }
	 }
	 break;
	 case 2:
	 // anarchic Flickering
	 for (uint8_t i = 0; i <= 5; i++) {
	 randomSeed(analogRead(ledPins[i]));
	 analogWrite(ledPins[i],
	 MAX_BRIGHTNESS - random(variation, variation * 2));
	 }
	 break;
	 */
//	}
	isFlickering = false;
} //lightFlicker

/*
 * Colors are defined in percentage of brightness.
 *
 */
void getColor(uint8_t colorID) {
	switch (colorID) {
	case 0:
//Red
		currentColor.r = 100;
		currentColor.g = 0;
		currentColor.b = 0;
		break;
	case 1:
//Yellow
		currentColor.r = 100;
		currentColor.g = 100;
		currentColor.b = 0;
		break;
	case 2:
//Green
		currentColor.r = 0;
		currentColor.g = 100;
		currentColor.b = 0;
		break;
	case 3:
//Aqua
		currentColor.r = 0;
		currentColor.g = 100;
		currentColor.b = 100;
		break;
	case 4:
//Blue
		currentColor.r = 0;
		currentColor.g = 0;
		currentColor.b = 100;
		break;
	case 5:
//Fuschia
		currentColor.r = 100;
		currentColor.g = 0;
		currentColor.b = 100;
		break;

	case 6:
//DarkGrey
		currentColor.r = 66;
		currentColor.g = 66;
		currentColor.b = 66;
		break;
	case 7:
//DarkOrange
		currentColor.r = 100;
		currentColor.g = 55;
		currentColor.b = 0;
		break;
	case 8:
//DarkViolet
		currentColor.r = 58;
		currentColor.g = 0;
		currentColor.b = 83;
		break;
	case 9:
//DodgerBlue
		currentColor.r = 12;
		currentColor.g = 56;
		currentColor.b = 100;
		break;
	case 10:
//Gold
		currentColor.r = 100;
		currentColor.g = 84;
		currentColor.b = 0;
		break;
	case 11:
//GoldenRod
		currentColor.r = 85;
		currentColor.g = 65;
		currentColor.b = 12;
		break;
	case 12:
//Indigo
		currentColor.r = 29;
		currentColor.g = 0;
		currentColor.b = 51;
		break;
	case 13:
//LightGreen
		currentColor.r = 56;
		currentColor.g = 93;
		currentColor.b = 56;
		break;

	default:
// White (if enough voltage)
		currentColor.r = 100;
		currentColor.g = 100;
		currentColor.b = 100;
		break;
	}
} //getColor
#else

#endif
