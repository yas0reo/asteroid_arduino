/// Le code minimal

#include <Arduino.h>
#include <Chrono.h>
#include <Bounce2.h>
#include <MicroOscSlip.h>

MicroOscSlip<128> monOsc(&Serial);
Chrono chronoPot;
Bounce2::Button bouton;

#define POTENTIOMETER_PIN A3
void setup()
{
    Serial.begin(115200);
    pinMode(3, OUTPUT);
}

void loop()
{
    monOsc.onOscMessageReceived(traiterMessageOsc); // ACQUISITION DES MESSAGES

    if (chronoPot.hasPassed(20))
    {                        // SI LE CHRONO DÉPASSE 20 MILLISECONDES
        chronoPot.restart(); // REPARTIR LE CHRONO

        // LE 3 CI-BAS CORRESPOND À LA BROCHE ANALOGIQUE A3
        int valeur = analogRead(3); // LECTURE DE LA TENSION DE LA BROCHE A3 ENTRE 0 ET 1023

        monOsc.sendInt("/photo", valeur); // ENVOYER LA VALEUR
    }
}

// FONCTION APPELÉE LORSQU’UN MESSAGE OSC EST REÇU
void traiterMessageOsc(MicroOscMessage &message)
{
    // SI L’ADRESSE DU MESSAGE EST "/lumiere" ET QUE LE MESSAGE CONTIENT UN ARGUMENT ENTIER ("i") :
    if (message.checkOscAddressAndTypeTags("/lumiere", "i"))
    {

        int valeur = message.nextAsInt(); // RÉCUPÉRER L’ENTIER ("i")

        digitalWrite(3, valeur); // ASSIGNER LA VALEUR A LA DEL
    }
}
