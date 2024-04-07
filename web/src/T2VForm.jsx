import {Button} from "@radix-ui/themes";

export default function T2VForm() {

    const submitTextToSpeech = (value) => {
        const ttsInput = document.getElementById("tts-input");
        console.log(ttsInput);
    }


    return(
        <>
            <input type="text" id="tts-input" />
            <Button onClick={ () => submitTextToSpeech() }>Say it</Button>
        </>
    )
}