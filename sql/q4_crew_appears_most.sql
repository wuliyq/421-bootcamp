SELECT p.name, COUNT(c.person_id) AS NUM_APPEARANCES
FROM crew c
JOIN people p ON c.person_id = p.person_id
GROUP BY c.person_id
ORDER BY NUM_APPEARANCES DESC
LIMIT 20;