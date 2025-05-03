-- write your queries to insert data here

INSERT into client (id, first_name, last_name, email)
VALUES
(1, 'Sara', 'Smith', 'smiths@hello.com'),

(2, 'Miguel', 'Cabrera', 'mc@hello.com'),

(3, 'Bo', "Chan'g", 'bochang@hello.com');

INSERT into employee (id, first_name, last_name, start_date, email)
VALUES
(1, 'Ananya', 'Jaiswal', '20080410', 'ajaiswal@hello.com'),

(2, 'Michael', 'Fern', '20150719', 'michaelf@hello.com'),

(3, 'Abdul', 'Rehman', '20180227', 'rehman@hello.com');

INSERT into project (id, title, comments, cid)
VALUES (
    1, 'Diamond', 'Should be done by Jan 2019', (SELECT id FROM client WHERE first_name = 'Sara' AND last_name = 'Smith')
);

INSERT into project (id, title, comments, cid)
VALUES (
    2, "Chan'g", 'Ongoing maintenance', (SELECT id FROM client WHERE first_name = 'Bo' AND last_name = "Chan'g")
);


INSERT into project (id, title, comments, cid)
VALUES (
    3, 'The Robinson Project', 'NULL', (SELECT id FROM client WHERE first_name = 'Miguel' AND last_name = 'Cabrera')
);

INSERT into works_on (pid, eid, due_date)
VALUES (
    (SELECT id FROM project WHERE title = "Chan'g"), 
    (SELECT id FROM employee WHERE first_name = 'Ananya' AND last_name = 'Jaiswal'),
    '20201119'
);

INSERT into works_on (pid, eid, due_date)
VALUES (
    (SELECT id FROM project WHERE title = 'The Robinson Project'), 
    (SELECT id FROM employee WHERE first_name = 'Michael' AND last_name = 'Fern'),
    '20201205'
);

INSERT into works_on (pid, eid, due_date)
VALUES (
    (SELECT id FROM project WHERE title = 'Diamond'), 
    (SELECT id FROM employee WHERE first_name = 'Abdul' AND last_name = 'Rehman'),
    '20210101'
);
-- Leave the queries below untouched. These are to test your submission correctly.
select * from project;
select * from client;
select * from employee;
select * from works_on;
