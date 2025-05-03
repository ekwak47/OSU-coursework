-- Find the first_name and last_name of all actors who have never been in an Animation film.
-- Order by the actor_id in ascending order.

-- Put your query for q4 here

SELECT 
    actor.actor_id,
    actor.first_name,
    actor.last_name
FROM 
    actor
JOIN 
    film_actor ON actor.actor_id = film_actor.actor_id
WHERE 
    actor.actor_id NOT IN (
        SELECT 
            actor.actor_id
        FROM 
            actor
        JOIN 
            film_actor ON actor.actor_id = film_actor.actor_id
        JOIN 
            film_category ON film_actor.film_id = film_category.film_id
        JOIN 
            category ON film_category.category_id = category.category_id AND category.name = 'Animation'
        GROUP BY 
            actor.actor_id
    )
GROUP BY 
    actor.actor_id
ORDER BY 
    actor.actor_id ASC;