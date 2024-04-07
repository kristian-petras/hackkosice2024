import {Button, Card, Flex, TextArea} from "@radix-ui/themes";

export default function T2VForm() {

    const submitTextToSpeech = (value) => {
        const ttsInput = document.getElementById("tts-input");
        console.log(ttsInput);
    }


    return(
        <Card mt="3">
            <Flex direction="column" gapY="4" pt="2" pb="3" align="center">
                <TextArea size="3" style={{ width: "100%", marginBottom: "40px", height: "160px" }} color="gray" variant="soft" placeholder="Hello World!" />
                <Button style={{ width: "350px" }} onClick={ () => submitTextToSpeech() }>Speak🗣️</Button>
            </Flex>
        </Card>
    )
}