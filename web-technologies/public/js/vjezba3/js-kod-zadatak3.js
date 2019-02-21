document.getElementById("dugme").addEventListener("click", () => {
    let string = document.getElementById("tekst").value;

    let numbers = string.match(/\d+/g).map(Number);


    let jedinice = ["", "ijedan", "idva", "itri", "icetiri", "ipet", "isest", "isedam", "iosam", "idevet"];
    let desetice = ["", "dvadeset", "trideset", "cetrdeset", "pedeset", "sesdeset", "sedamdeset", "osamdeset", "devedeset"];
    let stotice = ["", "stotinu", "dvijestotine", "tristotine", "cetiristotine", "petstotina", "seststotina", "sedamstotina", "osamstotina",
        "devetstotina"
    ];
    let jediniceHiljade = ["", "jedna", "dvije", "tri", "cetiri", "pet", "sest", "sedam", "osam", "devet"];
    let jediniceMiliona = ["", "jedan", "dva", "tri", "cetiri", "pet", "sest", "sedam", "osam", "devet"];
    let deseticeposebno = ["deset", "jedanaest", "dvanaest","trinaest","cetrnaest","petnest","sestnest","sedamnaest","osamnaest","devetnaest"];

    let stringoviBrojeva = {};
    numbers.forEach(element => {
        let finalniString = "";

        let zadnja2 = element % 100;
        let jeLi = 0;
        for (let i = 0; i < 10; ++i) {
            if (i + 10 == zadnja2) {
                finalniString += deseticeposebno[i];
                jeLi = 1;
                break;
            }
        }

        if (!jeLi) {
            let zadnji = element % 10;
            let pred = Math.floor(zadnja2 / 10);
            let index = pred - 1;
            if (pred == 0) index = 0;
            finalniString += desetice[index] + jedinice[zadnji];
        }

        let treciOdKraja = element % 1000;
        let treciK = Math.floor(treciOdKraja / 100);

        finalniString = stotice[treciK] + finalniString;

        let noviElement = Math.floor(element / 1000);


        if (noviElement > 0 && noviElement < 1000000) {
            let broj = noviElement % 100;
            let stringMal = "";

            if (broj >= 10 && broj < 20) finalniString = deseticeposebno[broj - 10] + "hiljada" + finalniString;
            else {
                let brojZadnjaCifra = broj % 10;
                if (brojZadnjaCifra >= 2 && brojZadnjaCifra <= 4) stringMal = "hiljade";
                else stringMal = "hiljada";
                finalniString = jediniceHiljade[brojZadnjaCifra] + stringMal + finalniString;

                let pred = Math.floor(broj / 10);
                let index = pred - 1;
                if (pred == 0) index = 0;

                finalniString = desetice[index] + finalniString;

            }

            let treciOdKraja = noviElement % 1000;
            let treciK = Math.floor(treciOdKraja / 100);

            finalniString = stotice[treciK] + finalniString;

            let noviElement2 = Math.floor(noviElement / 1000);

            if (noviElement2 > 0 && noviElement2 < 1000) {
                let broj = noviElement2 % 100;
                let stringMal = "";

                if (broj >= 10 && broj < 20) finalniString = deseticeposebno[broj - 10] + "miliona" + finalniString;
                else {
                    let brojZadnjaCifra = broj % 10;
                    if (brojZadnjaCifra == 1) stringMal = "milion";
                    else stringMal = "miliona";
                    finalniString = jediniceMiliona[brojZadnjaCifra] + stringMal + finalniString;

                    let pred = Math.floor(broj / 10);
                    let index = pred - 1;
                    if (pred == 0) index = 0;

                    finalniString = desetice[index] + finalniString;
                }

                let treciOdKraja = noviElement2 % 1000;
                let treciK = Math.floor(treciOdKraja / 100);

                finalniString = stotice[treciK] + finalniString;
            }
        }

        stringoviBrojeva[element] = finalniString;
    });

    let noviString = string;
    console.log(numbers);

    for (let i = 0; i < numbers.length; ++i) {
        noviString = noviString = noviString.replace(String(numbers[i]), stringoviBrojeva[numbers[i]]);
    }
    document.getElementById("tekst").value = noviString;
});