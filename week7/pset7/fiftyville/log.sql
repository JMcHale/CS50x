-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To get an initial overview of the database structure and data within
.schema

-- Create a suspects table
CREATE TABLE suspects (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id));

-- Make EVERYONE a suspect
INSERT INTO suspects
SELECT *
FROM people;

-- Find out basic info on the crime using date, and place
SELECT *
FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- Description of this shows that the id is 295, at 10:15am, interviews conducted with three witnesses, at the bakery

-- Find the relevant interviews by looking on the correct date and searching for "bakery". There are four interviews for some reason???? Emma interviewed later perhaps???
SELECT *
FROM interviews
WHERE year = 2021 AND day = 28 AND month = 7 AND transcript LIKE '%bakery%';
-- The made a phonecall for less than a minute, and one for half an hour.
-- Within ten mins of the theft, they drove away and should be seen on footage
-- They planned to take a flight out on the 29th from fiftyville, the other person on the call purchased the flight
-- They withdrew money at the ATM earlier in the day

-- To find possible license plates within 10 mins of the crime, leaving the bakery
SELECT license_plate
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND (minute <= 25 AND minute >= 15);

-- To find the withdrawls from the ATM for that day
SELECT *
FROM bank_accounts
WHERE account_number IN
(SELECT account_number
FROM atm_transactions
WHERE atm_location = "Humphrey Lane" AND month = 7 AND year = 2021 AND day = 28 AND transaction_type = "withdraw");

-- To find phonecall, duration in seconds, less than a minute
SELECT *
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- To find all flights from fiftyville than happened on 29th, and the passengers on this flight by passport number
SELECT *
FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
JOIN passengers ON flights.id = passengers.flight_id
WHERE full_name = "Fiftyville Regional Airport" AND month = 7 AND year = 2021 AND day = 29 LIMIT 30;

-- To see who matches these passport numbers
SELECT *
FROM people
WHERE passport_number IN
(SELECT passport_number
FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
JOIN passengers ON flights.id = passengers.flight_id
WHERE full_name = "Fiftyville Regional Airport" AND month = 7 AND year = 2021 AND day = 29) LIMIT 30;

-- Attempting to combine all the queries to narrow down suspects
SELECT *
FROM people
LEFT JOIN bank_accounts
ON people.id = bank_accounts.person_id
WHERE passport_number IN
(SELECT passport_number
FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
JOIN passengers ON flights.id = passengers.flight_id
WHERE full_name = "Fiftyville Regional Airport" AND month = 7 AND year = 2021 AND day = 29)
AND license_plate IN
(SELECT license_plate
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND (minute <= 25 AND minute >= 15))
AND phone_number IN
(SELECT caller
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60);

-- Removing the ones without bank accounts, and only keeping those with transactions on the day
SELECT *
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
WHERE passport_number IN
(SELECT passport_number
FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
JOIN passengers ON flights.id = passengers.flight_id
WHERE full_name = "Fiftyville Regional Airport" AND month = 7 AND year = 2021 AND day = 29)
AND license_plate IN
(SELECT license_plate
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND (minute <= 25 AND minute >= 15))
AND phone_number IN
(SELECT caller
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
AND account_number IN
(SELECT account_number
FROM bank_accounts
WHERE account_number IN
(SELECT account_number
FROM atm_transactions
WHERE atm_location = "Humphrey Lane" AND month = 7 AND year = 2021 AND day = 28 AND transaction_type = "withdraw"));

-- ATM was on Leggett Street! No results for other query!!!
SELECT *
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
WHERE passport_number IN
(SELECT passport_number
FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
JOIN passengers ON flights.id = passengers.flight_id
WHERE full_name = "Fiftyville Regional Airport" AND month = 7 AND year = 2021 AND day = 29)
AND license_plate IN
(SELECT license_plate
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND (minute <= 25 AND minute >= 15))
AND phone_number IN
(SELECT caller
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
AND account_number IN
(SELECT account_number
FROM bank_accounts
WHERE account_number IN
(SELECT account_number
FROM atm_transactions
WHERE atm_location = "Leggett Street" AND month = 7 AND year = 2021 AND day = 28 AND transaction_type = "withdraw"));

-- ATM test
SELECT *
FROM bank_accounts
WHERE account_number IN
(SELECT account_number
FROM atm_transactions
WHERE atm_location = "Leggett Street" AND month = 7 AND year = 2021 AND day = 28 AND transaction_type = "withdraw");

-- They took the EARLIEST flight at 8:20
SELECT *
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
WHERE passport_number IN
(SELECT passport_number
FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
JOIN passengers ON flights.id = passengers.flight_id
WHERE full_name = "Fiftyville Regional Airport" AND month = 7 AND year = 2021 AND day = 29 AND hour = 8)
AND license_plate IN
(SELECT license_plate
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND (minute <= 25 AND minute >= 15))
AND phone_number IN
(SELECT caller
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
AND account_number IN
(SELECT account_number
FROM bank_accounts
WHERE account_number IN
(SELECT account_number
FROM atm_transactions
WHERE atm_location = "Leggett Street" AND month = 7 AND year = 2021 AND day = 28 AND transaction_type = "withdraw"));

-- IT WAS BRUCE!

-- To find accomplice number
SELECT *
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller LIKE '(367) 555-5533';

-- To find accomplice name
SELECT *
FROM people
WHERE phone_number IN
(SELECT receiver
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller LIKE '(367) 555-5533');

-- Accomplice is ROBIN!

-- To find flight they took
SELECT * FROM passengers WHERE passport_number = 5773159633;
-- Flight 36

-- Find Destination airport
SELECT * FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = 36);
-- They went to LaGuardia Airport, New York City
