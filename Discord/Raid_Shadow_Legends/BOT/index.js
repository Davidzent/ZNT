const Discord = require('discord.js');
const token = "NzAyOTY0MjA0MjEwMDk0MjMx.XqHs8w.jTvCooKF1W4j5VuRfZatauaRlXg";
const bot = new Discord.Client();
const prefix="-";
const prefixch="!";
const db = require('./Databas/database');
const Member = require('./Models/member');
const Score  = require('./Models/Scores');
const Task   = require('./Models/Task');
const Boss   = require('./Models/ClanBoss');
const ytdl=require('ytdl-core');
const queue = new Map();

bot.login(token);
bot.on('ready', () => {
    bot.user.setActivity("with depression", {
        type: "STREAMING",
        url: "https://www.twitch.tv/zentlnel"
    });
        console.log('This bot is online!');
        db.authenticate()
                .then(() => console.log("Logged in to DB."))
                .catch(err => console.log(err));
        Boss.init(db);
        Member.init(db);
        Task.init(db);
        Score.init(db);
        Boss.sync();
        Task.sync();
        Score.sync();
        Member.sync();
});
/********************************************************************************************************************************************************/
//New Members
bot.on ("guildMemberAdd", member => {
    member.guild.channels.cache.get("741026842877755543").send(
        '**' + member.user.username + '**, has joined the server! ' + emoji("741068844084363385") + " " + emoji("741115989592244286"));
    member.roles.add(['741001885997072466']);
});

/********************************************************************************************************************************************************/
//Do something when a message is send
bot.on("message", (message) =>{
    const serverQueue = queue.get(message.guild.id);
    let cmd = message.content.toUpperCase();
    let sender= message.author;
    let cont=message.content.slice(prefix.length).split(" ");
    let args=cont.slice(1);
    
/********************************************************************************************************************************************************/
    if(message.author.bot){}
    //Commands for everyone
    else if(cmd===prefix+"HELP"){
        message.channel.send(
                "```\n-Command: Can Be Used By Everyone\n"+
                "-Hello: Hello Command \n"+
                "-show username: Dispays Player Info\n"+
                "-Play link: Adds The Song Of The Link To A Queue\n"+
                "-SKIP: Skips Current Song\n"+
                "-Join: Bot Join Your Voice Chat\n"+
                "\n!Command: Can Only Be Used By Admins or Leaders\n"+
                "!Stop: Stop Current Queue\n"+
                "!CHC username Type: Changes Player Info\n"+
                "!DEL username: Delete A Player\n"+
                "!ADD username lvl: Adds A New Player\n"+
                "\n-CHC Command Types\n"+
                "-LVL  ###: Change User Level\n"+
                "-BOSS DAY: Change Clan Participation In Boss\n"+
                "\n~Easter Eggs~: Find them\n```");
    }
    else if(cmd===prefix+"HELLO"){
        message.reply("Hi my friend.");
    }
    else if (cmd.startsWith(prefix+"SKIP")) {
        message.reply("Skiping song");    
        skip(message, serverQueue);
    }
    else if(cmd.startsWith(prefix+"PLAY")){
        execute(message, serverQueue);
    }
    else if(cmd.startsWith(prefixch+"JOIN")){
        join(message);
    }else if(cmd.startsWith(prefixch+"SHOW")){
        console.log("work");
        show(message, serverQueue);
    }
    //Commands for Admins
    //Stops queue
    else if (cmd.startsWith(prefixch+"STOP")) {
        if(message.member.roles.cache.some(role => role.name === 'Leader')
           ||message.member.roles.cache.some(role => role.name === 'Admin')){
            message.reply("Stoping song");    
            stop(message, serverQueue);
        }
        else {
            message.reply("Not in required role ask the owner for permission.");
        }
    }

/********************************************************************************************************************************************************/
    //Emojis
    else if(cmd.startsWith(prefix+'1')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Yeah').toString();
        emoji("123");
        message.delete();
        message.channel.send(lel);
    }else if(cmd.startsWith(prefix+'2')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Sadcat').toString();
        message.delete();
        message.channel.send(lel);
    }else if(cmd.startsWith(prefix+'3')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Men').toString();
        message.delete();
        message.channel.send(lel);
    }else if(cmd.startsWith(prefix+'4')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Heart').toString();
        message.delete();
        message.channel.send(lel);
    }else if(cmd.startsWith(prefix+'5')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Fight').toString();
        message.delete();
        message.channel.send(lel);
    }else if(cmd.startsWith(prefix+'6')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Fdance').toString();
        message.delete();
        message.channel.send(lel);
    }else if(cmd.startsWith(prefix+'7')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'crapdance').toString();
        message.delete();
        message.channel.send(lel);
    }else if(cmd.startsWith(prefix+'8')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Cheers').toString();
        message.delete();
        message.channel.send(lel);
    }
    
    /********************************************************************************************************************************************************/
    //Database
    //Change a value from the database
    else if(cmd.startsWith(prefix+'SHOW')){
        Show(message,args);
    }
    else if(cmd.startsWith(prefixch+'CHC')){
        if(message.member.roles.cache.some(role => role.name === 'Leader')
                ||message.member.roles.cache.some(role => role.name === 'Admin')){
            Change(message,args);
        }
        else {
            message.reply("Not in required role ask the owner for permission.");
        }
    }
    else if(cmd.startsWith(prefixch+'DEL')){
        if(message.member.roles.cache.some(role => role.name === 'Leader')
                ||message.member.roles.cache.some(role => role.name === 'Admin')){
            Del(message,args);
        }
        else {
            message.reply("Not in required role ask the owner for permission.");
        }
    }
    else if(cmd.startsWith(prefixch+'ADD')){
        if(message.member.roles.cache.some(role => role.name === 'Leader')
                ||message.member.roles.cache.some(role => role.name === 'Admin')){
            Add(message,args);
        }
        else {
            message.reply("Not in required role ask the owner for permission.");
        }
    }
    //Secret commands
    else if(cmd.includes("WELCOME")){
        message.delete();
        message.reply('There are no welcomes in my server.');

    }
    else if(cmd.includes(" WK ")||cmd.includes("WELCOM")||cmd.startsWith("WK ")){
        message.reply("Spell it right You lazy.");
    }
});


/********************************************************************************************************************************************************/
//Functions
async function execute(message, serverQueue) {
    const args = message.content.split(" ");
    const voiceChannel = message.member.voice.channel;

    if (!voiceChannel)
        return message.channel.send("You need to be in a voice channel to play music!");
    const permissions = voiceChannel.permissionsFor(message.client.user);
    if (!permissions.has("CONNECT") || !permissions.has("SPEAK")) {
        return message.channel.send("I need the permissions to join and speak in your voice channel!");
    }
    const songInfo = await ytdl.getInfo(args[1]);
    const song = {
        title: songInfo.title,
        url: songInfo.video_url,
    };
    if (!serverQueue) {
        // Creating the contract for our queue
        const queueContruct = {
            textChannel: message.channel,
            voiceChannel: voiceChannel,
            connection: null,
            songs: [],
            size: 0,
            volume: 5,
            playing: true
    };
        // Setting the queue using our contract
        queue.set(message.guild.id, queueContruct);
        // Pushing the song to our songs array
        queueContruct.songs.push(song);
        
        try {
            // Here we try to join the voicechat and save our connection into our object.
            var connection = await voiceChannel.join();
            queueContruct.connection = connection;
            // Calling the play function to start a song
            play(message.guild, queueContruct.songs[0]);
            queueContruct.size++; 
        } catch (err) {
            // Printing the error message if the bot fails to join the voicechat
            console.log(err);
            queue.delete(message.guild.id);
            return message.channel.send(err);
        }

    } else {
        serverQueue.songs.push(song);
        serverQueue.size++;
        return message.channel.send(`${song.title} has been added to the queue!`);
  }
}

//Playlist functions
function play(guild, song) {
    const serverQueue = queue.get(guild.id);
    if (!song) {
        serverQueue.voiceChannel.leave();
        queue.delete(guild.id);
        return;
    }
    let dispatcher = serverQueue.connection.play(ytdl(song.url)).on("finish", () => {
        serverQueue.songs.shift();
        play(guild, serverQueue.songs[0]);
    }).on("error", error => console.error(error));
    dispatcher.setVolumeLogarithmic(serverQueue.volume / 5);
    serverQueue.textChannel.send(`Start playing: **${song.title}**`);
}

async function join(message){
    const voiceChannel = message.member.voice.channel;
    if (!voiceChannel)
        return message.channel.send("You need to be in a voice channel to play music!");
    const permissions = voiceChannel.permissionsFor(message.client.user);
    if (!permissions.has("CONNECT") || !permissions.has("SPEAK")) {
        return message.channel.send("I need the permissions to join and speak in your voice channel!");   
    }
    var connection = await voiceChannel.join();
}

function show(message,serverQueue){
    let s = "```\n";
    for(let i=0;i<serverQueue.size&&i<10;i++){
        s += '['+ (i+1).toString() + '] \t';
        s += serverQueue.songs[i].title.toString();
        s += '\n';
    }
    s += '```';
    console.log(s);
    message.channel.send(s);
}

function skip(message, serverQueue) {
    if (!message.member.voice.channel)
        return message.channel.send("You have to be in a voice channel to stop the music!");
    if (!serverQueue)
        return message.channel.send("There is no song that I could skip!");
    serverQueue.connection.dispatcher.end();
}

function stop(message, serverQueue) {
    if (!message.member.voice.channel)
        return message.channel.send("You have to be in a voice channel to stop the music!");
  serverQueue.songs = [];
  serverQueue.connection.dispatcher.end();
}

/********************************************************************************************************************************************************/
//Database functions
async function Change(message,args){
    args[0] = args[0].toUpperCase();
    if(!args[1]){
        message.channel.send("You need to put a what you want to change name and a new value \nEX: !chc type nickname new-value");
    }
    else if(args[0]==='WEEK'){
        args[1] = args[1].toUpperCase();
        if( args[1]==='ALL' ){
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
            const boss = await Boss.findOne({ where: { Nickname: args[1] } });
            if (boss === null) {
                message.channel.send("There is no member with the nickname: "+args[1]);
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
                        args[1]);
            }
        }
    }
    else if(!args[2]){
        message.channel.send("You need to put a what you want to change name and a new value \nEX: !chc type nickname new-value");
    }
    else{
        if(args[0]==='LVL'){
            let i=0;
            while(args[1][i])
                if(args[1][i]<'0'||args[1][i++]>'9')
                    return message.channel.send("The level must be a number between 60 and 1");
            const member = await Member.findOne({ where: { Nickname: args[2] } });
            if (member === null) {
                message.channel.send("There is no member with the nickname: "+args[2]);
            }else{    
                var lvl = parseInt(args[1]);
                if(lvl>60||lvl<1)
                     return message.channel.send("The level must be a number between 60 and 1");
                const task = await Task.findOne({ where: { Nickname: args[2] } });
                task.LVL = lvl;
                member.LVL = lvl;
                await member.save();
                await task.save();
                // Now the member was updated in the database!
                message.channel.send("The Level Was Succesfully Change");
            }
        }
        else if(args[0]==='BOSS'){
            args[1] = args[1].toUpperCase();
            if( args[1]!=='MON' && args[1]!=='TUE' && args[1]!=='WED' && args[1]!=='THU' &&
                    args[1]!=='FRI' && args[1]!=='SAT' && args[1]!=='SUN' ){
             return message.channel.send("That is not a valid day. Valid days are :Mon, Tue, Wed, Thu, Fri, Sat, Sun\n"+
                     "Your input : " + args[1]);
            }
            var i=0;
            var s="Succesfully change for " + args[0] + " Day: " + args[1] + " Members: ";
            while(args[2+i]){
                if(i>0)s+=", ";
                const boss = await Boss.findOne({ where: { Nickname: args[2+i] } });
                if (boss === null) {
                    message.channel.send("There is no member with the nickname: "+args[2+i]);
                }else{
                    s+=args[2+i];
                    switch(args[1]){
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
            message.channel.send("That is Wrong");
        }
    }
}

async function Del(message,args){
    if(!args){
        message.channel.send("You need to put the nickname of the person you want to erase \nEX: !Del nickname");
    }
    else{
        const member = await Member.findOne({ where: { Nickname: args[0] } });
        if (member === null) {
            message.channel.send("There is no member with the nickname: "+args[0]);
        }else{    
            const task = await Task.findOne({ where: { Nickname: args[0] } });
            const score = await Score.findOne({ where: { Nickname: args[0] } });
            const boss = await Boss.findOne({ where: { Nickname: args[0] } });
            await score.destroy();
            await member.destroy();
            await task.destroy();
            await boss.destroy();
            // Now the member was updated in the database!
            message.channel.send("The User Was Succesfully Deleted");
        }
    }
}

async function Add(message,args){
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
}

async function Show(message,args){    
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
            message.channel.send("```\nNickname       : " + args[0] + 
                    "\nLevel          : " + member.LVL + 
                    "\nTotal Score    : " + member.TOTALSCORE +
                    "\nMonday Boss    : " + (boss.BOSSMON?"Yes":"No") +
                    "\nTuesday Boss   : " + (boss.BOSSTUE?"Yes":"No") +
                    "\nWednesday Boss : " + (boss.BOSSWED?"Yes":"No") +
                    "\nThursday Boss  : " + (boss.BOSSTHU?"Yes":"No") +
                    "\nFriday Boss    : " + (boss.BOSSFRI?"Yes":"No") +
                    "\nSaturday Boss  : " + (boss.BOSSSAT?"Yes":"No") +
                    "\nSunday Boss    : " + (boss.BOSSSUN?"Yes":"No")+ "```");
        }
    }
    
}

/********************************************************************************************************************************************************/
//Custom emoji function
async function emoji(id){
    //let lel = bot.emojis.cache.filter(emojis => emojis.animated == true);
    //console.log(lel.cache);
    
    //return bot.emojis.cache.get(id).toString();
}