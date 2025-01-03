-- Keep a log of any SQL queries you execute as you solve the mystery.

-- CRIME SCENE REPORT
--      Theft time- 10:15 a.m.
--      Locaion- Humphrey Street bakery
--      3 witnesses present

--      Littering at 4:36 pm: no witnesses



-- INTERVIEWS
--      Ruth- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--            If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
--      Eugene- I don't know the thief's name, but it was someone I recognized.
--              Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
--      Raymond-  As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--                In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--                The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- BAKERY_SEC_LOG:
        select * from people join bakery_security_logs on bakery_security_logs.license_plate = people.license_plate
   ...> where year = 2023 and month = 7 and day = 28 and hour >= 10 and hour < 11 and activity = 'exit' and minute > 15 and minute < 25;
/*
+--------+---------+----------------+-----------------+---------------+-----+------+-------+-----+------+--------+----------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate | id  | year | month | day | hour | minute | activity | license_plate |
+--------+---------+----------------+-----------------+---------------+-----+------+-------+-----+------+--------+----------+---------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       | 260 | 2023 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | 261 | 2023 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       | 262 | 2023 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       | 263 | 2023 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       | 264 | 2023 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       | 265 | 2023 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       | 266 | 2023 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       | 267 | 2023 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
+--------+---------+----------------+-----------------+---------------+-----+------+-------+-----+------+--------+----------+---------------+
*/
-- ATM_TRANS:
    select * from people
   ...> join bank_accounts on bank_accounts.person_id = people.id
   ...> join atm_transactions on bank_accounts.account_number = atm_transactions.account_number
   ...> where transaction_type = 'withdraw' and atm_location = 'Leggett Street' and atm_transactions.account_number in
   ...> (select account_number from bank_accounts where person_id in
   ...> (select people.id from people join bakery_security_logs on bakery_security_logs.license_plate = people.license_plate where year = 2023 and month = 7 and day = 28 and hour >= 10 and hour < 11 and activity = 'exit' and minute > 15 and minute < 25));
/*
+--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+-----+----------------+------+-------+-----+----------------+------------------+--------+
|   id   | name  |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          | 39  | 49610011       | 2023 | 7     | 26  | Leggett Street | withdraw         | 10     |
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          | 267 | 49610011       | 2023 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 514354    | 2012          | 336 | 26013199       | 2023 | 7     | 28  | Leggett Street | withdraw         | 35     |
| 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       | 25506511       | 396669    | 2014          | 288 | 25506511       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       | 28500762       | 467400    | 2014          | 246 | 28500762       | 2023 | 7     | 28  | Leggett Street | withdraw         | 48     |
+--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+-----+----------------+------+-------+-----+----------------+------------------+--------+
*/

-- PHONE_CALL:
    select * from people where phone_number in
   ...> (select caller from phone_calls where year = 2023 and month = 7 and day = 28 and duration < 60 and caller in
   ...>   (select phone_number from people where id in
   ...>   (select person_id from bank_accounts where account_number in
   ...>    (select account_number from atm_transactions where transaction_type = 'withdraw' and atm_location = 'Leggett Street' and atm_transactions.account_number in
   ...>    (select account_number from bank_accounts where person_id in
   ...>    (select people.id from people join bakery_security_logs on bakery_security_logs.license_plate = people.license_plate where year = 2023 and month = 7 and day = 28 and hour >= 10 and hour < 11 and activity = 'exit' and minute > 15 and minute < 25))))));
/*
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+-------+----------------+-----------------+---------------+
*/

-- flights of another day
    select * from flights where year = 2023 and month = 7 and day = 29 order by hour;
/*
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
| 43 | 8                 | 1                      | 2023 | 7     | 29  | 9    | 30     |
| 23 | 8                 | 11                     | 2023 | 7     | 29  | 12   | 15     |
| 53 | 8                 | 9                      | 2023 | 7     | 29  | 15   | 20     |
| 18 | 8                 | 6                      | 2023 | 7     | 29  | 16   | 0      |
+----+-------------------+------------------------+------+-------+-----+------+--------+
*/
-- all flights have same origit_airport_id i.e. 8


-- flights whose id is 8
    select * from airports where id = 8;
/*
+----+--------------+-----------------------------+------------+
| id | abbreviation |          full_name          |    city    |
+----+--------------+-----------------------------+------------+
| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
+----+--------------+-----------------------------+------------+
*/

-- passengers onboard the flight:
    select name from people where passport_number in
   ...> ( select passport_number from passengers where flight_id = 36);

/*
+--------+
|  name  |
+--------+
| Kenny  |
| Sofia  |
| Taylor |
| Luca   |
| Kelsey |
| Edward |
| Bruce  |
| Doris  |
+--------+
*/
-- only Bruce out of all suspects board the flight next day from Fiftyville
-- which means he is the thief

-- Accomplice would be the one who was on the phone call with Bruce after the theft
    select name from people where phone_number in
   ...> (select receiver from phone_calls where year = 2023 and month = 7 and day = 28 and duration < 60 and caller = '(367) 555-5533');
/*
+-------+
| name  |
+-------+
| Robin |
+-------+
*/

-- so Robbin is the accomplice
