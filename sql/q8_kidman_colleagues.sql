SELECT DISTINCT(p.name) 
FROM people p
JOIN crew c ON p.person_id = c.person_id
JOIN titles t ON c.title_id = t.title_id
WHERE t.title_id IN (
    SELECT t.title_id
    FROM titles t
    JOIN crew c ON t.title_id = c.title_id
    JOIN people p ON c.person_id = p.person_id
    WHERE p.name = 'Nicole Kidman'
)
ORDER BY p.name;