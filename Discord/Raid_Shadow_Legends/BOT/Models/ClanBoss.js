const {DataTypes, Model} = require('sequelize');

module.exports = class ClanBosses extends Model {
    static init(sequelize){
        return super.init({
            Nickname:{
                type: DataTypes.STRING,
                autoIncrement: false,
                primaryKey: true
            },
            BOSSMON: { 
                type: DataTypes.BOOLEAN,
                defaultValue: false
            },
            BOSSTUE: { 
                type: DataTypes.BOOLEAN,
                defaultValue: false
            },
            BOSSWED: { 
                type: DataTypes.BOOLEAN,
                defaultValue: false
            },
            BOSSTHU: { 
                type: DataTypes.BOOLEAN,
                defaultValue: false
            },
            BOSSFRI: { 
                type: DataTypes.BOOLEAN,
                defaultValue: false
            },
            BOSSSAT: { 
                type: DataTypes.BOOLEAN,
                defaultValue: false
            },
            BOSSSUN: { 
                type: DataTypes.BOOLEAN,
                defaultValue: false
            }
        },{
            tablename: 'ClanBosses',
            timestamps: false,
            sequelize
        });
    }
};