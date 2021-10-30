//Conectors
const YTPlay=require('./YTPlay/YTPlay');

//Discord Music queue
const queue = new Map();

module.exports={
queue,
/********************************************************************************************************************************************************/
//Play list Functions
    execute: async function (message, serverQueue,args,Discord) {
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
        //console.log(args);
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
        let songInfo;
        if(args[0].includes(yt)||args[0].includes(yt2)){
            //console.log("By url")
            songInfo = await (await YTPlay.getInfo(args[0])).videoDetails;
            if(!songInfo)return message.channel.send("No:heart:");
            //console.log(songInfo.lengthSeconds);
            t.setSeconds(songInfo.lengthSeconds);
            song.title = songInfo.title;
            song.url = songInfo.video_url.toString();
            song.TS = parseInt(songInfo.lengthSeconds);
            song.thumbnail = songInfo.thumbnail[0].url;
            song.tlenght=t.toISOString().substr(11,8);

        }else if(args[0].includes(spotify)){
            return message.reply("Command is in progress");
        }else{
            //default search by name (going to change just temporaly)
            //get the first search in youtube
            url = await (await YTPlay.getFirstSearch(args));

            //get the info with the link 
            songInfo = await (await YTPlay.getInfo(url)).videoDetails;
            if(!songInfo)return message.channel.send("No:heart:");
            //console.log(songInfo.lengthSeconds);
            t.setSeconds(songInfo.lengthSeconds);
            song.title = songInfo.title;
            song.url = songInfo.video_url.toString();
            song.TS = parseInt(songInfo.lengthSeconds);
            song.thumbnail = songInfo.thumbnail[0].url;
            song.tlenght=t.toISOString().substr(11,8);
            
        }
        //console.log(songInfo);
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
                await play(message.guild, queueContruct.songs[0]);
                queueContruct.size++; 
            } catch (err) {
                // Printing the error message if the bot fails to join the voicechat
                //console.log(err);
                queue.delete(message.guild.id);
                return message.channel.send(err);
            }
        } else {
            delete t;
            t=new Date(0);
            let temp = new Date(0);
            //console.log(serverQueue.time);
            temp.setSeconds(serverQueue.time);
            //console.log(temp.toISOString().substr(11,8));
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
    },
    join: async function (message,serverQueue){
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
    },

    que: function (message,serverQueue,args,Discord){
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
    },

    skip: function (message, serverQueue) {
        if (!message.member.voice.channel)
            return message.channel.send("You have to be in a voice channel to stop the music!");
        if (!serverQueue)
            return message.channel.send("There is no song that I could skip!");
        if(serverQueue.connection.dispatcher)serverQueue.connection.dispatcher.end();
    },

    stop: function (message,serverQueue) {
        if (!message.member.voice.channel)
            return message.channel.send("You have to be in a voice channel to stop the music!");
        if(!serverQueue)return message.channel.send("There is no play list to stop in your current voice channel");
        serverQueue.voiceChannel.leave();
    }
}

async function play(guild, song) {
    let t = new Date(0);
    const serverQueue = queue.get(guild.id);
    if (!song) {
        serverQueue.voiceChannel.leave();
        queue.delete(guild.id);
        return;
    }
    //console.log(song.url);
    let dispatcher = serverQueue.connection.play(await YTPlay(song.url,{
        filter: "audio",
        //opusEncoded: true,
        //encoderArgs: ['-af', 'bass=g=10,dynaudnorm=f=200']
    })).on("finish", () => {
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