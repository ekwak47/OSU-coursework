
// Get an instance of mysql for app.js
var mysql = require('mysql')

// Create a 'connection pool' using the provided credentials
var pool = mysql.createPool({
    connectionLimit: 10,
    host: 'classmysql.engr.oregonstate.edu',
    user: '*',
    password: '*',
    database: '*'
})

// Export 
module.exports.pool = pool;
