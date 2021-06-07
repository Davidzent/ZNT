
//Required libraries
const Discord = require('discord.js');

//Discord Bot Token
const token=require('./extras/token').token;

//Database
const Database=require('./extras/Database');

//Music
const Music=require('./extras/Music');

//Discord extras
const bot = new Discord.Client();
const prefix="-";
const prefixch="!";

/****************************************************************************************************************************** */
//Discord Commands Definitions
const spm = "<@297774423715348480> Mimi";//297774423715348480
const comand="-Help\n-Hello\n-play\n-skip\n-queue\n-join\n-stop\n-nini\n-0\n\n\n-#\n-show\n!chc\n!del\n!add";
const meaning="Show available commands\nSaludate\nplays a song\nskip current song"
             +"\nshow the playlist queue\njoin a voice server\nstops the queue\nnini"
             +"\nshows emojies that can be used by bot or display one emoji with some name"
             +"\nshows most used emojis"
             +"\nshows one member stats\nchange one member stats\ndeletes a member\nadds a meber to the database";
const example="-Help\n-Hello\n-p The Moss or -p (youtube url)\n-s or -Skip\n-q or -queue\n-j or -join\n-Stop\n-nini I need help"
             +"\n-0 and -0 eridance\n\n\n-1 or -2 or -3...\n-show znt\n!chc week znt or !chc lvl znt 60\n!del znt\n!add znt";

//**************************************************************************************************************************** */
bot.login(token);
bot.on('ready', () => {
    bot.user.setActivity("with depression", {
        type: "STREAMING",
        url: "https://www.twitch.tv/zentlnel"
    });
    console.log('This bot is online!');
    Database.init();

});
/********************************************************************************************************************************************************/
//New Members
bot.on ("guildMemberAdd", member => {
    member.guild.channels.cache.get("741026842877755543").send(
        '**' + member.user.username + '**, has joined the server! ' + emoji("741068844084363385") + " " + emoji("741115989592244286"));
    member.roles.add(['741001885997072466']);
});

/********************************************************************************************************************************************************/
/*bot.on("messageReactionAdd",(reaction)=>{
});*/
//Do something when a message is send


bot.on("message", (message) =>{
    //if the message came from a bot do nothing

    if(message.author.bot){
        if(message.author.username=="Mudae"){
            message.react('💘');
        }
        return 0;
    }
    
    //variables
    let g = "none";
    let mr = "none";
    if(message.guild)g = Music.queue.get(message.guild.id);
    const serverQueue = g;
    if(message.guild) mr=message.member.roles.cache;
    let mrol = mr;
    let cmd = message.content.toUpperCase();
    let cont=message.content.slice(prefix.length).split(" ");
    let args=cont.filter(e=>e).slice(1);
    //console.log(args);

    
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
    else if (g!="none"&&cmd.startsWith(prefix+"SK")) {
        let t=new Date(0);
        let repeat=1;
        message.reply("Skiping song");  
        //console.log(args);
        if(args[0])repeat=parseInt(args[0]);
        repeat--;
        Music.skip(message, serverQueue);
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
        Music.execute(message, serverQueue,args,Discord);
    }
    else if(g!="none"&&cmd===prefix+"J"){
        Music.join(message);
    }else if(g!="none"&&cmd.startsWith(prefix+"Q")){
        Music.que(message, serverQueue,args,Discord);
    }
    else if (g!="none"&&cmd===prefix+"STOP") {
        if(mrol.some(role => role.name === 'Leader')||mrol.some(role => role.name === 'Admin')){
            message.reply("Stoping song");    
            Music.stop(message, serverQueue);
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
        Database.Show(message,args);
    }
    else if(mrol!="none"&&cmd.startsWith(prefixch+'CHC')){
        if(mrol.some(role => role.name === 'Leader')||mrol.some(role => role.name === 'Admin')){
            Database.Change(message,args);
        }
        else {
            message.reply("Not in required role ask the owner for permission.");
        }
    }
    else if(mrol!="none"&&cmd.startsWith(prefixch+'DEL')){
        if(mrol.some(role => role.name === 'Leader')||mrol.some(role => role.name === 'Admin')){
            Database.Del(message,args);
        }
        else {
            message.reply("Not in required role ask the owner for permission.");
        }
    }
    else if(mrol!="none"&&cmd.startsWith(prefixch+'ADD')){
        if(mrol.some(role => role.name === 'Co-Leader')||mrol.some(role => role.name === 'Leader')){
            Database.Add(message,args);
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
        let sentence="";
        if (message.reference){
            let test="";
            //console.log(message.reference);
            message.channel.messages.fetch({ limit: 50 }).then(msgs => {
                //console.log(`Received ${msgs.size} messages`);
                //Iterate through the messages here with the variable "messages".
                
                msgs.forEach(msgs => {
                    if(msgs.id==message.reference.messageID){
                        //console.log(msgs.content.replace(/a|e|o|u/gi,"i")+" ");
                        sentence+=msgs.content.replace(/a|e|o|u/gi,"i");
                        message.channel.send(sentence);
                        message.delete();
                    }
                    });
                });
        }
        else{
            for(let i=0;i<args.length;i++){
                sentence+=args[i].replace(/a|e|o|u/gi,"i")+" ";
            }
            message.channel.send(sentence);
            message.delete();
        }
    }
    else if(cmd===prefix+"T"){
        message.delete();
        /*for(let i=0; i<1000 ;i++){
            message.channel.send(spm)
            .then(msg => {
                msg.delete({timeout: 10000});
            });
        } 
        //message.channel.send("▬▬▬▬▬▬:radio_button:▬▬▬▬▬▬");
        
        //message.channel.send("Yes"); 
        */
    }

});

