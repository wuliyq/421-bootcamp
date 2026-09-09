SELECT ((t.premiered / 10) * 10) || 's' AS DECADE, ROUND(AVG(r.rating), 2) AS AVG_RATING, MAX(r.rating) AS TOP_RATING, MIN(r.rating) AS MIN_RATING, COUNT(t.title_id) AS NUM_RELEASES
FROM ratings r
JOIN titles t ON r.title_id = t.title_id
WHERE t.premiered IS NOT NULL
GROUP BY DECADE
ORDER BY AVG_RATING DESC, DECADE ASC;