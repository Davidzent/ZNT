const Discord = require('discord.js');
const bot = new Discord.Client();
const token = "Njk2MTM0NTU4MTA5Nzk0NDU2.XolGZw.Q5ySrPwinbKAW09rb6mDjJDgRxs";
const prefix="-";
const prefixch="!";
//const ytdl=require('ytdl-core');
//const queue = new Map();
//var RTG="April 25";
//var RD="April 16";
//var RB="To be announced";
//var SE='April 15, Spring card activities begin.';


bot.on('ready', ()=>{
	console.log('This bot is online!');
    
})
bot.login(token);

/*bot.on("message", (message) =>{
    const serverQueue = queue.get(message.guild.id);
    let cmd = message.content.toUpperCase();
    let sender= message.author;
    let cont=message.content.slice(prefix.length).split(" ");
    let args=cont.slice(1);
    if(message.author.bot){}
    else if(cmd===prefix+"HELLO"){
        message.reply("Hi my friend.");
    }
    else if(cmd===prefix+"RTG"){
        message.channel.send("Next RTG will be on "+RTG);
    }
    else if(cmd===prefix+"RD"){
        message.channel.send("Next RD will be on "+RD);
    }
    else if(cmd===prefix+"RB"){
        message.channel.send("Next RB will be on "+RB);
    }
    else if(cmd===prefix+"SE"){
        message.channel.send("Next SE will be on "+SE);
    }
    else if (cmd.startsWith(prefix+"SKIP")) {
        message.reply("Skiping song");    
        skip(message, serverQueue);
    }else if (cmd.startsWith(prefixch+"STOP")) {
        if(message.member.roles.cache.some(role => role.name === 'COMUNIX')
           ||message.member.roles.cache.some(role => role.name === 'Admin')){
            message.reply("Stoping song");    
            stop(message, serverQueue);
        }
        else {
            message.reply("Not in required role ask the owner for permission.");
        }
    }
    else if(cmd.startsWith(prefix+"PLAY")){
        execute(message, serverQueue);
    }
    else if(cmd.startsWith(prefixch+"JOIN")){
        //var connection = await voiceChannel.join();
    }
    else if(cmd.startsWith(prefixch+"RTG")){
        if(message.member.roles.cache.some(role => role.name === 'COMUNIX')||message.member.roles.cache.some(role => role.name === 'Admin')){
                message.reply("Succesfully changed");    
                RTG=args[0];
                for(var i=1;i<args.length;i++){
                    RTG+=" "+args[i];
                }

            }
            else {
                message.reply("Not in required role ask the owner for permission.");
            }
    }
    else if(cmd.startsWith(prefixch+"RD")){
        //Checks for required role
        if(message.member.roles.cache.some(role => role.name === 'COMUNIX')||message.member.roles.cache.some(role => role.name === 'Admin')){
                message.reply("Succesfully changed");    
                RD=args[0];
                for(var i=1;i<args.length;i++){
                    RD+=" "+args[i];
                }

            }
            else {
                message.reply("Not in required role ask the owner for permission.");
            }
    }
    else if(cmd.startsWith(prefixch+"RB")){
            if(message.member.roles.cache.some(role => role.name === 'COMUNIX')||message.member.roles.cache.some(role => role.name === 'Admin')){
                message.reply("Succesfully changed");    
                RB=args[0];
                for(var i=1;i<args.length;i++){
                    RB+=" "+args[i];
                }

            }
            else {
                message.reply("Not in required role ask the owner for permission.");
            }
        }
    else if(cmd.startsWith(prefixch+"SE")){
            if(message.member.roles.cache.some(role => role.name === 'COMUNIX')||message.member.roles.cache.some(role => role.name === 'Admin')){
                message.reply("Succesfully changed");    
                SE=args[0];
                for(var i=1;i<args.length;i++){
                    SE+=" "+args[i];
                }

            }
            else {
                message.reply("Not in required role ask the owner for permission.");
            }
        }
    else if(cmd.includes("WELCOME")){
        message.delete();
        message.reply('There are no welcomes in my server.');
        
    }
    else if(cmd.includes("WK")||cmd.includes("WELCOM")){
        message.reply("Spell it right You lazy.");
    }
    
})

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
        url: songInfo.video_url
    };
    if (!serverQueue) {
        // Creating the contract for our queue
        const queueContruct = {
            textChannel: message.channel,
            voiceChannel: voiceChannel,
            connection: null,
            songs: [],
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
        } catch (err) {
            // Printing the error message if the bot fails to join the voicechat
            console.log(err);
            queue.delete(message.guild.id);
            return message.channel.send(err);
        }
        
    } else {
        serverQueue.songs.push(song);
        return message.channel.send(`${song.title} has been added to the queue!`);
  }
}
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
function loadXMLDoc() {
  var xmlhttp = new XMLHttpRequest();
  xmlhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      myFunction(this);
    }
  };
  xmlhttp.open("GET", "../Strikes.xml", true);
  xmlhttp.send();
}
function myFunction(xml) {
  var i;
  var xmlDoc = xml.responseXML;
  var table="Nickname \t\t Strikes";
  var x = xmlDoc.getElementsByTagName("Strikes");
  for (i = 0; i <x.length; i++) { 
    table += "\n" +
    x[i].getElementsByTagName("Nickname")[0].childNodes[0].nodeValue +
    " \t\t " +
    x[i].getElementsByTagName("Strikes")[0].childNodes[0].nodeValue +
    "\n";
  }
  message.channel.send(table);
}*/