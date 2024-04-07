import {Button, Card, Flex, TextArea} from "@radix-ui/themes";
import {useState} from "react";

export default function T2VForm() {
    const [text, setText] = useState("");

    const saveText = (event) => {
        setText(event.target.value);
    };

    const submitTextToVoice = () => {
        const url = 'http://127.0.0.1:8000/say_text';
        const origin = 'http://127.0.0.1:3000'; // Client origin

        console.log(text)
        fetch(url, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Origin': origin
            },
            body: text
        })
            .then(response => {
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }

                return response.json();
            })
            .then(data => {
                console.log('Response:', data);
            })
            .catch(error => {
                console.error('Error:', error);
            });
    };


    return(
        <Card mt="4">
            <Flex direction="column" gapY="4" pt="2" pb="3" align="center">
                <TextArea size="3" style={{ width: "100%", marginBottom: "40px", height: "160px" }} color="gray" variant="soft" placeholder="Hello World!" onChange={saveText}/>
                <Button style={{ width: "350px" }} onClick={ () => submitTextToVoice() }>Speak🗣️</Button>
            </Flex>
        </Card>
    )
}