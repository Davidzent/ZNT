const {DataTypes, Model} = require('sequelize');

module.exports = class Scores extends Model {
    static init(sequelize){
        return super.init({
            Nickname:{
                type: DataTypes.STRING,
                autoIncrement: false,
                primaryKey: true
            },
            SCORE1: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            },
            SCORE2: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            },
            SCORE3: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            },
            SCORE4: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            },
            SCORE5: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            },
            SCORE6: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            },
            SCORE7: { 
                type: DataTypes.INTEGER,
                defaultValue: 0
            }
            
        },{
            tablename: 'Score',
            timestamps: false,
            sequelize
        });
    }
};
