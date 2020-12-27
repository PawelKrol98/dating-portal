import random
import string

male_names = ["Andrzej", "Bartek", "Cezary" ,"Dawid", "Pawel", "Daniel", "Jakub", "Maciek", "Piotr", "Filip", "Rafal",
              "Krzysiek", "Jan", "Jacek", "Julian", "Damian", "Oskar", "Kacper", "Konrad", "Kornel", "Arek", "Darek",
              "Marek", "Michal", "Igor", "Lucjan", "Ludwik", "Maks", "Mikolaj", "Norbert", "Aleksander", "Olaf"]
female_names = ["Agata", "Dominika", "Gabriela","Julia", "Natalia", "Agnieszka", "Monika", "Elwira", "Irena", "Weronika",
                "Wiktoria", "Asia", "Kasia", "Basia", "Walentyna", "Sylwia", "Sara", "Patrycja", "Paulina", "Nikola",
                "Miriam", "Martyna", "Marzena", "Ewelina", "Luiza", "Kaja", "Klaudia", "Krystyna", "Kamila"]
cities = ["Warszawa", "Krakow", "Wroclaw", "Gdansk", "Skoczow", "Bielsko", "Cieszyn", "Katowice", "Gdansk", "Sopot",
          "Bialystok", "Szczecin", "Rzeszow", "Przemysl", "Opole", "Poznan", "Lodz", "Bydgoszcz", "Lublin"]
hobbies = ["sport", "filmy", "gry", "jezyki", "moda", "pilka", "koszykowka", "bieganie", "czytanie", "ksiazki", "muzyka",
           "polityka", "historia", "it", "gitara", "spacery", "zwierzeta", "spiewanie", "gotowanie", "makijaz", "taniec"]
genders = ["W", "M"]

letters = string.ascii_lowercase

file =open("users.txt", "w")
for i in range(1, 10000):
    password = ''.join(random.choice(letters) for i in range(5))
    gender = random.choice(genders)
    if gender == "W":
        name = random.choice(female_names)
    else:
        name = random.choice(male_names)
    age = random.randint(18, 40)
    if gender == "W":
        if random.randrange(0,100) > 4: orientation = "M"
        elif random.randrange(0,100) > 50: orientation = "WM"
        else: orientation = "W"
    if gender == "M":
        if random.randrange(0,100) > 4: orientation = "W"
        elif random.randrange(0,100) > 50: orientation = "WM"
        else: orientation = "M"
    city = random.choice(cities)
    numberOf_hobbies = random.randint(2, 4)
    listOf_hobbies = random.sample(hobbies, numberOf_hobbies)
    hobby = ""
    for h in listOf_hobbies:
        hobby += (h + " ")
    user = str(i) + " " + password + " " +name + " " + gender + " " + str(age) + " " + orientation + " " + city + " hobby " + hobby + "\n"
    file.write(user)

file.close()
