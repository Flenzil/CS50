-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene description
SELECT description
FROM crime_scene_reports
WHERE month IS 7
AND day IS 28
AND street IS "Humphrey Street";
-- Crime took place at 10:15am at Humprhey Street bakery. Three witnesses.

-- Look at bakery security logs

SELECT hour, minute, activity, license_plate
FROM bakery_security_logs
WHERE day IS 28
AND month IS 7
AND (hour IS 9 OR hour IS 10);
-- Two lisence plates enter but don't leave just before 10:15: 13FNH73 & R3G7486

-- Match plates to names
SELECT *
FROM people
WHERE license_plate IS '13FNH73' OR 'R3G7486';
-- Match for Sophia, id: 745650

-- Check interviews for Sofia
SELECT *
FROM interviews
WHERE name IS "Sophia"

