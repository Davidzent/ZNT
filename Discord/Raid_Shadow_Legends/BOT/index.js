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
const yts=require('yt-search');
const queue = new Map();

/****************************************************************************************************************************** */
const spm = "<@297774423715348480> Mimi";//297774423715348480
const comand="-Help\n-Hello\n-play\n-skip\n-queue\n-join\n-stop\n-nini\n-0\n\n\n-#\n-show\n!chc\n!del\n!add";
const meaning="Show available commands\nSaludate\nplays a song\nskip current song"
             +"\nshow the playlist queue\njoin a voice server\nstops the queue\nnini"
             +"\nshows emojies that can be used by bot or display one emoji with some name"
             +"\nshows most used emojis"
             +"\nshows one member stats\nchange one member stats\ndeletes a member\nadds a meber to the database";
const example="-Help\n-Hello\n-p The Moss or -p (youtube url)\n-s or -Skip\n-q or -queue\n-j or -join\n-Stop\n-nini I need help"
             +"\n-0 and -0 eridance\n\n\n-1 or -2 or -3...\n-show znt\n!chc week znt or !chc lvl znt 60\n!del znt\n!add znt";
const plyrinfo= "\nLevel" +
                "\nTotal Score" +
                "\nMonday Boss" +
                "\nTuesday Boss" + 
                "\nWednesday Boss" + 
                "\nThursday Boss" +
                "\nFriday Boss" + 
                "\nSaturday Boss" +
                "\nSunday Boss"; 


                

//**************************************************************************************************************************** */
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
    //if the message came from a bot do nothing
    if(message.author.bot){return 0;}
    
    //variables
    let g = "none";
    let mr = "none";
    if(message.guild)g = queue.get(message.guild.id);
    const serverQueue = g;
    if(message.guild) mr=message.member.roles.cache;
    let mrol = mr;
    let cmd = message.content.toUpperCase();
    let cont=message.content.slice(prefix.length).split(" ");
    let args=cont.slice(1);

    
    /********************************************************************************************************************************************************/
    //Commands for everyone
    if(cmd===prefix+"HELP"){
        let q = new Discord.MessageEmbed()
        .setColor('#8865a0')
        .setTitle("Clan Mannager Help")
        .setURL("https://discord.com/api/oauth2/authorize?client_id=702964204210094231&permissions=0&scope=bot")
        .setAuthor(message.author.tag, message.author.avatarURL() .toString())
        .addFields(
            { name: "Commands", value: comand, inline: true },
            { name: "Meaning", value: (meaning), inline: true },
            { name: "example", value: (example), inline: true }
            )
        .setFooter('There are secret commands', "https://cdn.discordapp.com/app-icons/702964204210094231/24ffd4c80226d842d31aeabf7dc03f45.png?size=512");
        message.channel.send(q);
    }
    else if(cmd===prefix+"HELLO"||cmd===prefix+"HI"){
        message.reply("Hello there.");
    }

    /********************************************************************************************************************************************************/
    //Music commands
    else if (g!="none"&&cmd.startsWith(prefix+"S")) {
        let t=new Date(0);
        let repeat=1;
        message.reply("Skiping song");  
        if(args[0])repeat=parseInt(args[0]);
        repeat--;
        skip(message, serverQueue);
        for(let i=0;i<repeat&&i<serverQueue.size;i++){
            serverQueue.time -= serverQueue.songs[i].TS;
            serverQueue.songs.shift();
            serverQueue.size--;
            
        }
        t.setSeconds(serverQueue.time);
        serverQueue.tm=t.toISOString().substr(11,8);
        
    }
    else if(g!="none"&&cmd.startsWith(prefix+"P")){
        //message.delete({timeout: 5000});
        execute(message, serverQueue,args);
    }
    else if(g!="none"&&cmd.startsWith(prefix+"R")){
        //message.delete({timeout: 5000});
        random(message, serverQueue,args);
    }
    else if(g!="none"&&cmd===prefix+"J"){
        join(message);
    }else if(g!="none"&&cmd.startsWith(prefix+"Q")){
        que(message, serverQueue,args);
    }
    else if (g!="none"&&cmd===prefix+"STOP") {
        if(mrol.some(role => role.name === 'Leader')||mrol.some(role => role.name === 'Admin')){
            message.reply("Stoping song");    
            stop(message, serverQueue);
        }
        else {
            message.reply("Not in required role ask the owner for permission.");
        }
    }

    /********************************************************************************************************************************************************/
    //Emojis
    else if(cmd.startsWith(prefix+'0')&&!args[0]){
        message.delete();
        let lel="";     
        bot.emojis.cache.each(emojis => (lel+=emojis.toString()+" "));
        if(lel.length>2000){
            let lel2=lel.split(" ");
            let i=0;
            while(i<lel2.length){
                lel = "";
                while(lel.length<1900&&i<lel2.length)lel+=lel2[i++];
                message.channel.send(lel)
                .then(msg => {
                    msg.delete({timeout: 20000});
                });;
            }
        }
    }
    else if(cmd.startsWith(prefix+'0')){
        message.delete();
        let lel=bot.emojis.cache.find(emojis => emojis.name.toUpperCase() == args[0].toUpperCase());
        if(lel)message.channel.send(lel.toString());
        else message.reply("There is no such emoji as '"+ args[0]+"'");
    }
    else if(cmd===(prefix+'1')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Yeah').toString();
        message.delete();
        if(lel)message.channel.send(lel);
    }else if(cmd===(prefix+'2')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Sadcat').toString();
        message.delete();
        if(lel)message.channel.send(lel);
    }else if(cmd===(prefix+'3')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Men').toString();
        message.delete();
        if(lel)message.channel.send(lel);
    }else if(cmd===(prefix+'4')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Heart').toString();
        message.delete();
        if(lel)message.channel.send(lel);
    }else if(cmd===(prefix+'5')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Fight').toString();
        message.delete();
        if(lel)message.channel.send(lel);
    }else if(cmd===(prefix+'6')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Fdance').toString();
        message.delete();
        if(lel)message.channel.send(lel);
    }else if(cmd===(prefix+'7')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'crapdance').toString();
        message.delete();
        if(lel)message.channel.send(lel);
    }else if(cmd===(prefix+'8')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'Cheers').toString();
        message.delete();
        if(lel)message.channel.send(lel);
    }else if(cmd===(prefix+'9')){
        let lel=bot.emojis.cache.find(emojis => emojis.name == 'eridance').toString();
        message.delete();
        if(lel)message.channel.send(lel);
    }
    
    /********************************************************************************************************************************************************/
    //Database
    //Change a value from the database
    else if(mrol!="none"&&cmd.startsWith(prefix+'SHOW')){
        Show(message,args);
    }
    else if(mrol!="none"&&cmd.startsWith(prefixch+'CHC')){
        if(mrol.some(role => role.name === 'Leader')||mrol.some(role => role.name === 'Admin')){
            Change(message,args);
        }
        else {
            message.reply("Not in required role ask the owner for permission.");
        }
    }
    else if(mrol!="none"&&cmd.startsWith(prefixch+'DEL')){
        if(mrol.some(role => role.name === 'Leader')||mrol.some(role => role.name === 'Admin')){
            Del(message,args);
        }
        else {
            message.reply("Not in required role ask the owner for permission.");
        }
    }
    else if(mrol!="none"&&cmd.startsWith(prefixch+'ADD')){
        if(mrol.some(role => role.name === 'Co-Leader')||mrol.some(role => role.name === 'Leader')){
            Add(message,args);
        }
        else {
            message.reply("Not in required role ask the owner for permission.");
        }
    }
    /********************************************************************************************************************************************************/
    //Secret commands
    else if(cmd.includes("WELCOME")){
        message.delete();
        message.reply('There are no welcomes in my server.');

    }
    else if(cmd.includes(" WK ")||cmd.includes("WELCOM")||cmd.startsWith("WK ")){
        message.reply("Spell it right You lazy.");
    }
    /********************************************************************************************************************************************************/
    //Experiments / Unofficial commands
    else if(cmd.startsWith(prefix+"NINI")){
        message.delete();
        let sentence="";
        for(let i=0;i<args.length;i++){
            sentence+=args[i].replace(/a|e|o|u/gi,"i")+" ";
        }
        message.channel.send(sentence);
    }
    else if(cmd===prefix+"T"){
        message.delete();
        /*
        let u = message.guild.client.users.cache.find(user => user.username === "Noemi");
        for(let i=0;i<1;i++){
            u.send("funciono");
        }
        console.log("sending");
        message.delete();
        if(args[0]){
            const atchmnt= new Discord.MessageAttachment(args[0]);
            message.channel.send(atchmnt);
        }
        else message.channel.send("No file location");
        console.log(u);
        */
        message.delete();
        for(let i=0; i<1000 ;i++){
            message.channel.send(spm)
            .then(msg => {
                msg.delete({timeout: 10000});
            });
        } 
        //message.channel.send("▬▬▬▬▬▬:radio_button:▬▬▬▬▬▬");
        
        message.channel.send("Yes"); 
        
    }

});

/********************************************************************************************************************************************************/
//Play list Functions
async function random(message, serverQueue,args){
    let repeat=parseInt(args[args.length-1]);
    if(!repeat){
        repeat=10;
    }
    else{
        args[args.length-1]="";
    }
    for(let i=0;i<repeat;i++){
        console.log("run "+i);
        const voiceChannel = message.member.voice.channel;
        if (!voiceChannel)
            return message.channel.send("You need to be in a voice channel to play music!");
        const permissions = voiceChannel.permissionsFor(message.client.user);
        if (!permissions.has("CONNECT") || !permissions.has("SPEAK")) {
            return message.channel.send("I need the permissions to join and speak in your voice channel!");
        }
        let spotify = "/open.spotify.com/";
        let yt="/www.youtube.com/";
        let yt2="/youtube.com/";
        let t = new Date(0);
        let songInfo;
        const song = {
            title: "",
            url: "",
            requested: message.author.tag,
            tlenght: "",
            TS: "",
            thumbnail: "",
                
        };
        if(args[0].includes(yt)||args[0].includes(yt2)){
            songInfo = await ytdl.getInfo(args[0]);
            if(!songInfo)return message.channel.send("No:heart:");
            t.setSeconds(songInfo.length_seconds);
            song.title = songInfo.title;
            song.url = songInfo.video_url;
            song.TS = parseInt(songInfo.length_seconds);
            song.thumbnail = songInfo.player_response.videoDetails.thumbnail.thumbnails[0].url;
            song.tlenght=t.toISOString().substr(11,8);

        }else if(args[0].toUpperCase()+args[1].toUpperCase()==='ID'){
            args=args.toString().replace(/,|ID| /gi,"");
            try{
                songInfo = await ytdl.getInfo(args);
            }catch(err){
                console.log(err);
                args+=" "+repeat-i+1;
                return random(message,serverQueue,args);
            }
            if(!songInfo)return message.channel.send("No:heart:");
            t.setSeconds(songInfo.length_seconds);
            song.title = songInfo.title;
            song.url = songInfo.video_url;
            song.TS = parseInt(songInfo.length_seconds);
            song.thumbnail = songInfo.player_response.videoDetails.thumbnail.thumbnails[0].url;
            song.tlenght=t.toISOString().substr(11,8);
            

        }else if(args[0].includes(spotify)){
            return message.reply("Command is in progress");
        }else{
            let songname = await yts(args.toString().replace(/,/gi," ") + "lyrics");
            console.log(args[0]);
            console.log(args);
            //console.log(songname.videos[0]);
            let vid;
            let temp=0;
            do{
                vid = songname.videos[temp];
                //console.log(vid);
                //console.log(vid.url.toString().replace(/\/youtube.com\//gi,yt));
                try{
                    songInfo = await ytdl.getInfo(vid.url.toString().replace(/\/youtube.com\//gi,yt));
                }catch(err){
                    //console.log(songInfo);
                    //console.log(err);
                    //args[args.length]=repeat-i;
                    //return random(message,serverQueue,args);
                }
                
            }while(!songInfo&&(temp++)<songname.videos.length);
            if(temp>=songname.videos.length&&songInfo){
                do{
                    //console.log("new");
                    //console.log(queue.get(message.guild.id));
                    //console.log(songInfo.related_videos[x]);
                    args="ID ";
                    args+=songInfo.related_videos[x].id.toString();
                    //console.log(args);
                    b=(songInfo&&queue.get(message.guild.id))?queue.get(message.guild.id).songs.some(songs => songs.title === songInfo.related_videos[x].title):false;
                    //console.log(b);
                    //if(queue.get(message.guild.id)&&songInfo)console.log(queue.get(message.guild.id).songs.some(songs => songs.title === args));
                }while((b||parseInt(songInfo.related_videos[x++].length_seconds)>600)&&x<songInfo.related_videos.length);
                console.log("out because of exceed");
                args+=" "+repeat-i+1;
                return random(message,serverQueue,args);
            }
            //console.log("info");
            //console.log(queue.get(message.guild.id));
            //if(queue.get(message.guild.id)){
            //    console.log(songInfo);
            //    console.log(queue.get(message.guild.id).songs);
            //    songInfo?console.log(queue.get(message.guild.id).songs.some(songs => songs.title === songInfo.title)):0;
            //}
                
            t.setSeconds(songInfo.length_seconds);
            song.title = songInfo.title;
            song.url = songInfo.video_url;
            song.TS = parseInt(songInfo.length_seconds);
            song.thumbnail = songInfo.player_response.videoDetails.thumbnail.thumbnails[0].url;
            song.tlenght=t.toISOString().substr(11,8);
        }
        
        let b=false;
        let x=0;
        
        do{
            console.log("new");
            //console.log(queue.get(message.guild.id));
            //console.log(songInfo.related_videos[x]);
            args="ID ";
            args+=songInfo.related_videos[x].id.toString();
            //console.log(args);
            b=(songInfo&&queue.get(message.guild.id))?queue.get(message.guild.id).songs.some(songs => songs.title === songInfo.related_videos[x].title):false;
            console.log(b);
            if(queue.get(message.guild.id)&&songInfo){
                console.log(queue.get(message.guild.id).songs.some(songs => songs.title === songInfo.related_videos[x].title));
                console.log(songInfo.related_videos[x].title);
                console.log(queue.get(message.guild.id));
                console.log(songInfo.related_videos.length+" "+x);
            }
        }while((b||parseInt(songInfo.related_videos[x].length_seconds)>600)&&x++<songInfo.related_videos.length);
        //console.log(args);
        if (!serverQueue&&!queue.get(message.guild.id)) {
            // Creating the contract for our queue
            const queueContruct = {
                textChannel: message.channel,
                voiceChannel: voiceChannel,
                connection: null,
                songs: [],
                size: 0,
                volume: 5,
                playing: true,
                time: song.TS,
                tm: song.tlenght,
            };
            // Pushing the song to our songs array
            queueContruct.songs.push(song);
            // Setting the queue using our contract
            queue.set(message.guild.id, queueContruct);
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
            serverQueue=queue.get(message.guild.id);
            delete t;
            t=new Date(0);
            let temp = new Date(0);
            //console.log(serverQueue.time);
            temp.setSeconds(serverQueue.time);

            //Increase the time for the queue to end
            serverQueue.time += parseInt(song.TS);
            //console.log(serverQueue.time);
            t.setSeconds(serverQueue.time);
            serverQueue.tm = t.toISOString().substr(11,8);
            serverQueue.songs.push(song);
            serverQueue.size++;
            //Send message
            let q = new Discord.MessageEmbed()
            .setColor('#8865a0')
            .setTitle(song.title)
            .setURL(song.url)
            .setAuthor('Added to queue', message.author.avatarURL() .toString())
            .setThumbnail(song.thumbnail.toString());
            q.addFields(
                { name: "Song duration", value: (song.tlenght), inline: true },
                { name: "Estimated time until playing", value: (temp.toISOString().substr(11,8)), inline: true }
                );
            message.channel.send(q);
        }
    }
}
async function execute(message, serverQueue,args) {
    //https://open.spotify.com/playlist
    //https://www.youtube.com/
    //https://youtube.com/watch?v=GQ3V50XoLOM
    const voiceChannel = message.member.voice.channel;
    if (!voiceChannel)
        return message.channel.send("You need to be in a voice channel to play music!");
    const permissions = voiceChannel.permissionsFor(message.client.user);
    if (!permissions.has("CONNECT") || !permissions.has("SPEAK")) {
        return message.channel.send("I need the permissions to join and speak in your voice channel!");
    }
    console.log(args);
    let spotify = "/open.spotify.com/";
    let yt="/www.youtube.com/";
    let yt2="/youtube.com/";
    let t = new Date(0);
    const song = {
        title: "",
        url: "",
        requested: message.author.tag,
        tlenght: "",
        TS: "",
        thumbnail: "",
        
    };

    
    if(args[0].includes(yt)||args[0].includes(yt2)){
        console.log("By url")
        const songInfo = await ytdl.getInfo(args[0]);
        if(!songInfo)return message.channel.send("No:heart:");
        console.log(songInfo);
        t.setSeconds(song.TS);
        song.title = songInfo.title;
        song.url = songInfo.video_url;
        song.TS = songInfo.length_seconds;
        song.thumbnail = songInfo.player_response.videoDetails.thumbnail.thumbnails[0].url;
        song.tlenght=t.toISOString().substr(11,8);

    }else if(args[0].includes(spotify)){
        return message.reply("Command is in progress");
    }else{
        console.log("By Name");
        const songInfo = await yts(args.toString().replace(/,/gi," ") + "lyrics");
        let vid = songInfo.videos[0];
        console.log(vid);
        let tm=vid.timestamp.split(":");
        let seconds=0;
        let x=0;
        for(let i=parseInt(tm.length)-1;i>=0;i--){
            seconds+=parseInt(tm[i])*Math.pow(60,x++);
        }
        song.title=vid.title;
        song.url = vid.url;
        song.tlenght = vid.timestamp;
        song.thumbnail = vid.thumbnail;
        song.TS=seconds;
        
        /*
        //for future search function
        let size=10;
        let r = await yts(args.toString());
        let vid = r.videos.slice(0,size);
        let resp = '```';
        for(let i=0;i<size;i++){
            resp += (parseInt(i)+1) + "\t" + vid[i].title.toString() + '\n';
        }
        resp += '```';
        return message.channel.send(resp);
        */
    }
    
    if (!serverQueue) {
        // Creating the contract for our queue
        const queueContruct = {
            textChannel: message.channel,
            voiceChannel: voiceChannel,
            connection: null,
            songs: [],
            size: 0,
            volume: 5,
            playing: true,
            time: song.TS,
            tm: song.tlenght,
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
        delete t;
        t=new Date(0);
        let temp = new Date(0);
        temp.setSeconds(serverQueue.time);

        //Increase the time for the queue to end
        serverQueue.time += parseInt(song.TS);
        t.setSeconds(serverQueue.time);
        serverQueue.tm = t.toISOString().substr(11,8);
        serverQueue.songs.push(song);
        serverQueue.size++;

        //Send message
        let q = new Discord.MessageEmbed()
        .setColor('#8865a0')
        .setTitle(song.title)
        .setURL("https://discord.com/api/oauth2/authorize?client_id=702964204210094231&permissions=0&scope=bot")
        .setAuthor('Added to queue', message.author.avatarURL() .toString())
        .setThumbnail(song.thumbnail.toString());
        q.addFields(
            { name: "Song duration", value: (song.tlenght), inline: true },
            { name: "Estimated time until playing", value: (temp.toISOString().substr(11,8)), inline: true }
            );
        return message.channel.send(q);
  }
}

function play(guild, song) {
    let t = new Date(0);
    const serverQueue = queue.get(guild.id);
    if (!song) {
        serverQueue.voiceChannel.leave();
        queue.delete(guild.id);
        return;
    }
    let dispatcher = serverQueue.connection.play(ytdl(song.url,{filter: "audioonly"})).on("finish", () => {
        serverQueue.songs.shift();
        serverQueue.size--;
        serverQueue.time -= song.TS;
        t.setSeconds(serverQueue.time);
        serverQueue.tm=t.toISOString().substr(11,8);
        play(guild, serverQueue.songs[0]);
    }).on("error", error => console.error(error));
    dispatcher.setVolumeLogarithmic(serverQueue.volume / 5);
    serverQueue.textChannel.send("**Start playing :notes: : `" + song.title + "`**");
}

async function join(message,serverQueue){
    const voiceChannel = message.member.voice.channel;
    if (!voiceChannel)
        return message.channel.send("You need to be in a voice channel to play music!");
    const permissions = voiceChannel.permissionsFor(message.client.user);
    if (!permissions.has("CONNECT") || !permissions.has("SPEAK")) {
        return message.channel.send("I need the permissions to join and speak in your voice channel!");   
    }
    if(!serverQueue){
        return message.channel.send("Someone is already using the bot");   
    
    }
    var connection = await voiceChannel.join();
}

function que(message,serverQueue,args){
    let lng=5;
    if(!serverQueue)return message.channel.send("There is no queue");
    if(!args[0]) args[0] = 0;
    else{
        args[0]--;
    }
    // inside a command, event listener, etc.
    let s="";
    let q = new Discord.MessageEmbed()
        .setColor('#8865a0')
        .setTitle('Queue')
        .setURL("https://discord.com/api/oauth2/authorize?client_id=702964204210094231&permissions=0&scope=bot")
        .setAuthor('Clan Manager', message.author.avatarURL() .toString())
        .setThumbnail(serverQueue.songs[0].thumbnail.toString());
    
    
    //Add First Song
    q.addFields({ name: "__Now Playing__", value: ("["+serverQueue.songs[0].title.toString()+"]" + "("+serverQueue.songs[0].url.toString()+") | `"
    + serverQueue.songs[0].tlenght + " Requested by: "+ serverQueue.songs[0].requested.toString()) + '`', inline: false});
    
    //Create a temporary string for the other songs
    let temp=0;
    if (args[0]==0)temp=1;
    for(let i=(temp+(args[0]*lng));i<serverQueue.size&&i<(lng*(args[0]+1));i++){
        if(serverQueue.songs[i])
            s+="`"+(i).toString()+". "+"`"+"["+serverQueue.songs[i].title.toString()+"]" + "("+serverQueue.songs[i].url.toString()+") | `"
            + serverQueue.songs[i].tlenght + " Requested by: "+ serverQueue.songs[i].requested.toString() + "`\n"; 
    }

    //add them to the MessageEmbed
    if(s!=="")
    q.addFields({ name: "__Next__", value: (s), inline: false });

    //Information about the queue
    if(serverQueue.size>1)
    q.addFields({name: "Info: ", value:"**" + (serverQueue.size-1).toString() + ' songs in queue | ' +
        serverQueue.tm + ' total length**'});
    q.setFooter('Page: ' + (args[0]+1)+ '/' + (Math.ceil(serverQueue.size/lng)).toString() , 
        message.author.avatarURL() .toString());
    //send it to discord
    message.channel.send(q);
}

function skip(message, serverQueue) {
    if (!message.member.voice.channel)
        return message.channel.send("You have to be in a voice channel to stop the music!");
    if (!serverQueue)
        return message.channel.send("There is no song that I could skip!");
    if(serverQueue.connection.dispatcher)serverQueue.connection.dispatcher.end();
}

function stop(message, serverQueue) {
    if (!message.member.voice.channel)
        return message.channel.send("You have to be in a voice channel to stop the music!");
    if(!serverQueue)return message.channel.send("There is no play list to stop in your current voice channel");
    if(serverQueue.songs!=undefined)serverQueue.songs = [];
    if(serverQueue.connection.dispatcher)serverQueue.connection.dispatcher.end();
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
    
}

/********************************************************************************************************************************************************/
//Custom emoji function
async function emoji(id){
    //let lel = bot.emojis.cache.filter(emojis => emojis.animated == true);
    //console.log(lel.cache);
    
    //return bot.emojis.cache.get(id).toString();
}