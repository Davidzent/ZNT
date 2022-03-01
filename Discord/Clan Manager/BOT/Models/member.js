const {DataTypes, Model} = require('sequelize');

module.exports = class Member extends Model {
    static init(sequelize){
        return super.init({
            Nickname:{
                type: DataTypes.STRING,
                autoIncrement: false,
                primaryKey: true
            },
            LVL: { 
                type: DataTypes.INTEGER,
                defaultValue: 1
            },
            TOTALSCORE: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            }            
        },{
            tablename: 'member',
            timestamps: false,
            sequelize
        });
    }
};
