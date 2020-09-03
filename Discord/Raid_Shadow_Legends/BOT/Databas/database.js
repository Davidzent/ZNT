
const Sequelize  = require('sequelize');

/*Sequelize("Database name","Username","Password",{
    dialect: 'mysql'
});
*/
module.exports = new Sequelize("Discord-clan","root","",{
    dialect: 'mysql'
});