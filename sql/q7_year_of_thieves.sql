-- WITH YEAR AS (
--     SELECT t.premiered
--     FROM titles t
--     WHERE t.primary_title = 'Army of Thieves'
-- )

-- SELECT COUNT(t.premiered) AS NUMBER_OF_TITLES, t.premiered 
-- FROM titles t
-- WHERE t.premiered = YEAR.premiered;
SELECT COUNT(t.premiered) AS NUMBER_OF_TITLES
FROM titles t
WHERE t.premiered = (
    SELECT t.premiered
    FROM titles t
    WHERE t.primary_title = 'Army of Thieves'
    LIMIT 1
);