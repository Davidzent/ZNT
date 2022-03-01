
//Display menu
const plyrinfo= "\nLevel" +
                "\nTotal Score" +
                "\nMonday Boss" +
                "\nTuesday Boss" + 
                "\nWednesday Boss" + 
                "\nThursday Boss" +
                "\nFriday Boss" + 
                "\nSaturday Boss" +
                "\nSunday Boss"; 

//Database libraries
const db    =   require('../Databas/database');
const Member=   require('../Models/member');
const Score =   require('../Models/Scores');
const Task  =   require('../Models/Task');
const Boss  =   require('../Models/ClanBoss');

module.exports={
    /********************************************************************************************************************************************************/
    //Database functions
    init: function (){
        db.authenticate()
                .then(() => {
                    console.log("Logged in to DB.");
                    Boss.init(db);
                    Member.init(db);
                    Task.init(db);
                    Score.init(db);
                    Boss.sync();
                    Task.sync();
                    Score.sync();
                    Member.sync();
                }).catch(err => console.log(err));
    },
    Change: async function (message,args){
        if(!args[0]){
            return message.channel.send('Include the username to change or if all include "all"');
        }
        args[0] = args[0].toUpperCase();
        
        if(!args[1]){
            return message.channel.send("Include the value to change. WEEK, LVL, BOSS");
        }
        args[1] = args[1].toUpperCase();
        if(args[1]==='WEEK'){
            if( args[0]==='ALL' ){
                // Find all users
                const boss = await Boss.findAll();
                var i=0;
                while(boss[i]){
                    boss[i].BOSSMON=false;
                    boss[i].BOSSTUE=false;
                    boss[i].BOSSWED=false;
                    boss[i].BOSSTHU=false;
                    boss[i].BOSSFRI=false;
                    boss[i].BOSSSAT=false;
                    boss[i].BOSSSUN=false;
                    await boss[i++].save();
                }
                // Now the member was updated in the database!
                message.channel.send("The Boss Data was succesfully changed for ALL");
            }
            else{
                const boss = await Boss.findOne({ where: { Nickname: args[0] } });
                if (boss === null) {
                    message.channel.send("There is no member with the nickname: "+args[0]);
                }else{
                    boss.BOSSMON=false;
                    boss.BOSSTUE=false;
                    boss.BOSSWED=false;
                    boss.BOSSTHU=false;
                    boss.BOSSFRI=false;
                    boss.BOSSSAT=false;
                    boss.BOSSSUN=false;
                    await boss.save();
                    message.channel.send("The Boss Data was succesfully changed for "+
                            args[0]);
                }
            }
        }
        else if(!args[2]){
            message.channel.send("You need to include the value to change. EX: LVL 50, Boss Mon");
        }
        else{
            if(args[1]==='LVL'){
                let i=0;
                while(args[2][i])
                    if(args[2][i]<'0'||args[2][i++]>'9')
                        return message.channel.send("The level must be a number between 60 and 1");
                const member = await Member.findOne({ where: { Nickname: args[0] } });
                if (member === null) {
                    message.channel.send("There is no member with the nickname: "+args[0]);
                }else{    
                    var lvl = parseInt(args[2]);
                    if(lvl>60||lvl<1)
                        return message.channel.send("The level must be a number between 60 and 1");
                    const task = await Task.findOne({ where: { Nickname: args[0] } });
                    task.LVL = lvl;
                    member.LVL = lvl;
                    await member.save();
                    await task.save();
                    // Now the member was updated in the database!
                    message.channel.send("The Level Was Succesfully Change");
                }
            }
            else if(args[args.length-2].toUpperCase()==='BOSS'){
                let argsz=args.length-1;
                if(args[argsz])
                    args[argsz] = args[argsz].toUpperCase();

                if( args[argsz]!=='MON' && args[argsz]!=='TUE' && args[argsz]!=='WED' && args[argsz]!=='THU' &&
                        args[argsz]!=='FRI' && args[argsz]!=='SAT' && args[argsz]!=='SUN' ){
                return message.channel.send("That is not a valid day. Valid days are :Mon, Tue, Wed, Thu, Fri, Sat, Sun\n"+
                        "Your input : " + args[2]);
                }
                var i=0;
                var s="Succesfully change for " + args[0] + " Day: " + args[argsz] + " Members: ";
                while(args[i].toUpperCase()!="BOSS"){
                    if(i>0)s+=", ";
                    const boss = await Boss.findOne({ where: { Nickname: args[0+i] } });
                    if (boss === null) {
                        message.channel.send("There is no member with the nickname: "+args[i]);
                    }else{
                        s+=args[0+i];
                        switch(args[argsz]){
                            case 'MON':{
                                    boss.BOSSMON = !boss.BOSSMON;
                                    break;
                            }
                            case 'TUE':{
                                    boss.BOSSTUE = !boss.BOSSTUE;
                                    break;
                            }
                            case 'WED':{
                                    boss.BOSSWED = !boss.BOSSWED;
                                    break;
                            }
                            case 'THU':{
                                    boss.BOSSTHU = !boss.BOSSTHU;
                                    break;
                            }
                            case 'FRI':{
                                    boss.BOSSFRI = !boss.BOSSFRI;
                                    break;
                            }
                            case 'SAT':{
                                    boss.BOSSSAT = !boss.BOSSSAT;
                                    break;
                            }
                            case 'SUN':{
                                    boss.BOSSSUN = !boss.BOSSSUN;
                                    break;
                            }
                        }
                        await boss.save();
                        // Now the member was updated in the database!
                    }
                    i++;
                }
                message.channel.send(s);
            }
            else{
                //console.log(args[args.length-2]);
                message.channel.send("That is Wrong");
            }
        }
    },

    Del: async function (message,args){
        if(!args){
            message.channel.send("You need to put the nickname of the person you want to erase \nEX: !Del nickname");
        }
        else{
            for(let i=0;i<args.length;i++){
                const member = await Member.findOne({ where: { Nickname: args[i] } });
                if (member === null) {
                    message.channel.send("There is no member with the nickname: "+args[i]);
                }else{    
                    const task = await Task.findOne({ where: { Nickname: args[i] } });
                    const score = await Score.findOne({ where: { Nickname: args[i] } });
                    const boss = await Boss.findOne({ where: { Nickname: args[i] } });
                    await score.destroy();
                    await member.destroy();
                    await task.destroy();
                    await boss.destroy();
                    // Now the member was updated in the database!
                    
                }
            }
            message.channel.send("The User/s Were Succesfully Deleted");
        }
    },

    Add: async function (message,args){
        if(!args[1]){
            message.channel.send("You need to put the nickname of the person you want to erase \nEX: !Add nickname lvl");
        }
        else{
            const member = await Member.findOne({ where: { Nickname: args[0] } });
            const task = await Task.findOne({ where: { Nickname: args[0] } });
            const score = await Score.findOne({ where: { Nickname: args[0] } });
            const boss = await Boss.findOne({ where: { Nickname: args[0] } });
            if(member !== null && task !== null && score !== null)
                return message.channel.send("There exist an user with the Nickname of: " + args[0]);
            let i=0;
            while(args[1][i])
                if(args[1][i]<'0'||args[1][i++]>'9')
                    return message.channel.send("The level must be a number between 60 and 1");
            var lvl = parseInt(args[1]);
            if(lvl>60||lvl<1)
                return message.channel.send("The level must be a number between 60 and 1");
            
            if(member===null){
                const member2 = await Member.create({Nickname: args[0], LVL: lvl});
                await member2.save();
            }
            if(task===null){
                const task2 = await Task.create({Nickname: args[0], LVL: lvl});
                await task2.save();
            }
            if(score===null){
                const score2 = await Score.create({Nickname: args[0]}); 
                await score2.save();
            }
            if(boss===null){
                const boss2 = await Boss.create({Nickname: args[0]}); 
                await boss2.save();
            }
            // Now the member was updated in the database!
            message.channel.send("The User Was Succesfully Created");
        }
    },

    Show: async function (message,args,Discord){    
        if(!args[0]){
            message.channel.send("You need to put a nickname \nEX: -show nickname");
        }
        else{
            const member = await Member.findOne({ where: { Nickname: args[0] } });
            const boss = await Boss.findOne({ where: { Nickname: args[0] } });
            if (member === null || boss === null) {
                message.channel.send("There is no member with the nickname: " + args[0]);
            }else{    
                // Now output players data
                let data = member.LVL+'\n'+ member.TOTALSCORE+'\n'+
                        (boss.BOSSMON?"Yes":"No") + '\n' +
                        (boss.BOSSTUE?"Yes":"No") + '\n' +
                        (boss.BOSSWED?"Yes":"No") + '\n' +
                        (boss.BOSSTHU?"Yes":"No") + '\n' +
                        (boss.BOSSFRI?"Yes":"No") + '\n' +
                        (boss.BOSSSAT?"Yes":"No") + '\n' +
                        (boss.BOSSSUN?"Yes":"No") + '\n';
                let q = new Discord.MessageEmbed()
                .setColor('#8865a0')
                .setTitle("Info of "+args[0])
                .setURL("https://discord.com/api/oauth2/authorize?client_id=702964204210094231&permissions=0&scope=bot")
                .setAuthor(message.author.tag, message.author.avatarURL().toString())
                .addFields(
                    { name: "Info", value: plyrinfo, inline: true },
                    { name: "Value", value: data, inline: true },
                    );
                message.channel.send(q);
                    
            }
        }
        
    },
}
