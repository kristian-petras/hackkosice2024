<!-- 
This repository is to show the cool project you created.
To make it easier to present, we created this sample, which you can edit and use for your HK project.
-->

![image](.template_images/Top.png)

<p align="center">
  <a href="https://hackkosice.com">
    <img src="https://github.com/hackkosice/i-demoed-hk24/assets/41269745/156db290-9b9f-47b3-9268-3c7381081144" height="300px">
  </a>
</p>

&nbsp;

<!--
In the next part, we recommend displaying all important shields for your project: https://github.com/badges/shields
-->

[![All Contributors](https://img.shields.io/github/contributors/hackkosice/i-demoed-hk24?style=flat-square)](https://github.com/hackkosice/i-demoed-hk24/graphs/contributors)
[![Activity](https://img.shields.io/github/commit-activity/m/hackkosice/i-demoed-hk24?style=flat-square)](https://github.com/hackkosice/i-demoed-hk24/pulse)  
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](http://makeapullrequest.com)
[![first-timers-only Friendly](https://img.shields.io/badge/first--timers--only-friendly-blue.svg)](http://www.firsttimersonly.com/)

#Inspiration
Not everyone has access to a modern computer. But everyone should have access to music. Sometimes you just want to listen to some music on your STM32 microcontroller equipped with a piezo buzzer. We are passionate about challanges which force us to find an alternative ways, paths full of trial and error. Looking for making the most out of embedded hardware.

#What it does
Audio player board with TTS integration with an efficient hardware implementation and intuitive software user interface, consisting of an polished app written in React. Hardware user interface is utilizing 7 segment display with animations and leds for additional feedback for the user.

#How we built it
We opted to use popular Arduino framework as a base for our implementation of all the challange tasks. Based on processor speed and memory restrictions focused, to get the best possible quality sound reproduction. For that we created a pipeline of steps with backend python api pushing the audio data over serial line to the devBoard.

#Challenges we ran into
We ran into multiple challanges First of the challange was utilizing simple piezo element with it's native limited frequency range that required and creative thinking to implement audio playback and TTS with the most quality. Second challenge was implementing an effective way of delivering preprocessed audio data as a stream of blocks and buffering to fit into hw limitations of speed and size of memory.

#Accomplishments that we're proud of
We managed our time schedule and lack of sleep to implement all of the challange tasks.

#What we learned
We learned a lot about physics behing audio and how the sound waves can be created and modified. We also learned how to effectively find a way to deliver data using limited channels such as serial interface.

#What's next for Kompót
We are prepared to improve ourselves.

Built With
c,platformio,python,react


![image](.template_images/Mid.png)


## Other Project repositories

<!--
If your project is constructed out of multiple Repositories, you can specify them here:
-->

## Documentation

<!--
Documentation is a crucial part of every project, but also maybe during the hackathon, you did not have time to create it. We recommend coming back later and filling in this part, for example, with https://docs.github.com/en/communities/documenting-your-project-with-wikis/about-wikis
-->


## Contributors ✨

Thanks go to these wonderful people
<!--
Here, you can show off all your cool teammates with whom you created this project.
If you want to automate it, you can use a cool bot: https://allcontributors.org/
-->

## License

<!-- You can use this section to specify the license for this project under which it can be distributed. -->

## Thanks

<!-- You can use this section to thank people who helped you create this awesome project outside of your team -->

![image](.template_images/Bot.png)

