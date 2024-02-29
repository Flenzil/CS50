SELECT DISTINCT people.name
FROM people
JOIN stars
ON stars.person_id = people.id
JOIN movies
ON movies.id = stars.movie_id
WHERE movies.id IN
(
    SELECT movie_id
    FROM stars
    WHERE person_id IS
    (
        SELECT id
        FROM people
        WHERE name IS "Kevin Bacon"
        AND birth IS 1958
    )
)
AND people.name IS NOT "Kevin Bacon"

