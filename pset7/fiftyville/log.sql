-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Running all the time to understand the structure of the database
.schema
.tables

-- I know this happened on July 28, 2024, on Humphrey Street, looking into the crime scene reports for this time period.
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- From this I gather the theft was at the bakery at 10:15am, corroborated by three witnesses. Also "Littering" happened at 16:36, with no witnesses. Not sure what this means but it seems the bakery is our next point of interest.


Select activity, license_plate, id
From bakery_security_logs
WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 14 AND 16;
-- From this we gather  license plate number 13FNH73 entering the bakery and 5P2BI95 exiting, id numbers 259,260 respectively

-- Next I will see who is attached to these license plates, since they were the only two at the bakery at the time of the crime.
SELECT id, name, phone_number, passport_number
FROM people
WHERE license_plate = '13FNH73' OR license_plate = '5P2BI95';
-- We now have two suspects, id 21103 Vanessa with phone number 7255554692 and passport_number 2963008352 AND id 745650 Sophia 0275551068 and passport number 3642612721

-- Before moving on I want to see the interviews to gather more information that may be useful and see if I can figure out this 'littering' situation
SELECT transcript
FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28;
-- 1) I do get something that will expand my search from the bakery -  "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame."
-- 2) Seems like I have an ATM lead: Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- 3) Phone call in that same time frame: As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- 1) Back to the bakery, looking for license plates in the lot from 10:15-10:25am in that lot, for cars that left.
Select activity, license_plate, id
From bakery_security_logs
WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;
-- More License plates, all these left at that time: 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55, now to find out who they are.
SELECT id, name, phone_number, passport_number
FROM people
WHERE license_plate = '5P2BI95' OR license_plate = '94KL13X' OR license_plate = '6P58WS2' OR license_plate = '4328GD8' OR license_plate = 'G412CB7' OR license_plate = 'L93JTIZ' OR license_plate = '322W7JE' OR license_plate = '0NTHK55';
-- This results in the following people (id, name, phone #, passport #):  221103 | Vanessa | (725) 555-4692 | 2963008352  :  243696 | Barry   | (301) 555-4174 | 7526138472 :  396669 | Iman    | (829) 555-5269 | 7049073643 : 398010 | Sofia   | (130) 555-0289 | 1695452385 : 467400 | Luca    | (389) 555-5198 | 8496433585: 514354 | Diana   | (770) 555-1861 | 3592750733 : 560886 | Kelsey  | (499) 555-9472 | 8294398571  : 686048 | Bruce   | (367) 555-5533 | 5773159633


-- 2) We want to see if we can find people who were at the Leggett Street ATM prior to the crime at the bakery (10:15am) same day, and see if there is any crossover with the people who left the parking lot of the bakery in the suspected time frame.
SELECT id, account_number, transaction_type, amount
FROM atm_transactions
WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
-- WE have the following information (id, account_number, transaction_type, amount):  246 | 28500762       | withdraw         | 48  :  264 | 28296815       | withdraw         | 20   : 266 | 76054385       | withdraw         | 60    : 267 | 49610011       | withdraw         | 50 :  269 | 16153065       | withdraw         | 80     : 288 | 25506511       | withdraw         | 20  : 313 | 81061156       | withdraw         | 30  :  336 | 26013199       | withdraw         | 35
-- Now we take these account numbers and see if we can map them out to the names of the account owners, getting the person_id's first from the bank accounts

SELECT person_id
FROM bank_accounts
WHERE account_number = '28500762' OR account_number = '28296815' OR account_number = '76054385' OR account_number = '49610011'  OR account_number = '16153065' OR account_number = '25506511' OR account_number = '81061156' OR account_number = '26013199';
-- we get person id's: 686048    | 514354    |458378    |395717    |396669    |467400    |449774    |438727
-- Now let's get their info -
SELECT name
FROM people
WHERE id = '686048' OR id = '514354' OR id = '458378' OR id = '395717' OR id = '396669' OR id = '467400' OR id = '449774' OR id = '438727';
-- We get the following names: Kenny   |Iman    |Benista |Taylor  |Brooke  |Luca    |Diana   |Bruce - which we have got info on already - corresponds as the following when cross-referencing the licence plate owners leaving the bakery:
-- AS people (id, name, phone #, passport #): NO Kenny, 396669 | Iman    | (829) 555-5269 | 7049073643, NO Benista, NO Taylor, NO Brooke, 467400 | Luca    | (389) 555-5198 | 8496433585, 514354 | Diana   | (770) 555-1861 | 3592750733, 686048 | Bruce   | (367) 555-5533 | 5773159633

-- OK now we have 4 suspects:
-- 396669 | Iman    | (829) 555-5269 | 7049073643
-- 467400 | Luca    | (389) 555-5198 | 8496433585
-- 514354 | Diana   | (770) 555-1861 | 3592750733
-- 686048 | Bruce   | (367) 555-5533 | 5773159633


-- 3) Now time to check their phone logs, 10:15-10:20am 07/28/24, lasted less than a minute, mention of an early flight next day, other caller to purchase ticket.
SELECT caller, receiver
FROM phone_calls
WHERE month = 7 AND day = 28 AND year = 2024 AND duration <= 60;
-- This yeilds a reviever (389) 555-5198 or Luca, a caller (770) 555-1861 or Diana, and another caller (367) 555-5533 or Bruce. Since the witnessed said they saw the theif call, it narrows our suspect list to Diana who called number (725) 555-3243 and Bruce who called number (375) 555-8161.


-- Since we have two suspects (theifs), and their respective call revievers (accomplices). Diana : (725) 555-3243 OR Bruce : (375) 555-8161. So we have those relationships and can deduce who was involved by seaching the flight purchases and finding out which accomplice purchaced the ticket -- the witnessed heard this acccomplice be told to by a plane ticket for the next day. Next we will simply find out who the accomplices are.
SELECT name FROM people WHERE phone_number = '(725) 555-3243' OR phone_number = '(375) 555-8161';
-- This means the pairs are Diana : Phillip & Bruce : Robin

-- We can find the flight either one of the theifs are in by looking for passangers with passport numbers that match those of the suspects. Diana passport # is 3592750733 and Bruce passport # is 5773159633

SELECT flight_id, seat, passport_number
FROM passengers
WHERE passport_number = 3592750733 OR passport_number = 5773159633;

-- This thankfully yeilds two flights each which we can use to narrow down by time frame which would be on 7/29/24
-- Diana flight id's 18 seat 4C, 24 seat 2C, 54 seat 6C and Bruce's flight id is 36 seat 4A
SELECT id, origin_airport_id, destination_airport_id, hour, minute
FROM flights
WHERE year = 2024 AND month = 7 AND day = 29 AND (id = 18 OR id = 24 OR id = 54 OR id = 36);
-- We get two results flight DIANA: id 18, origin_airport_id 8, destination_airport_id 6, Time 16:00 AND BRUCE: id 36, origin_airport_id 8, destination_airport_id 4, time 8:20 ---- so these are our two flights of interest.
-- We know they wanted a flight our first thing in the morning according to the witness statement, this means we can assume the morning flight most likely had the theif on board - Bruce, and his accomplice was Robin.
SELECT id, abbreviation, full_name, city
FROM airports
WHERE id = 8 OR id = 4;
-- | id | abbreviation |          full_name          |     city      |
-- | 4  | LGA          | LaGuardia Airport           | New York City |
-- | 8  | CSF          | Fiftyville Regional Airport | Fiftyville    |
-- STORYLINE: Bruce hit the ATM that morning, left the bakery within 10 mins of the crime, called Robin while leaving. Robin booked the flight for Bruce who left Fiftyville Regional Airport in Fiftyville on a flight to LaGuardia Airport in New York City departing at 8:20am.

