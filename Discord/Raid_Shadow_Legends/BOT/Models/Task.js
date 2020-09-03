const {DataTypes, Model} = require('sequelize');

module.exports = class Task extends Model {
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
            STARS: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            },
            TIER: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            },
            CHEST: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            },
            INACTIVITY: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            },
            STRIKES: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            },
            SCORE: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            }
        },{
            tablename: 'Task',
            timestamps: false,
            sequelize
        });
    }
};
