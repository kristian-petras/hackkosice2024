import {Button, Card, Flex} from "@radix-ui/themes";

export default function PlayerInput() {
    async function submitFile(filePicker) {
        console.log("banan");
        // Construct a FormData instance
        const formData = new FormData();

        // Add a file
        const selection = filePicker.files;
        if (selection.length > 0) {
            console.log("jahoda");
            const file = selection[0];
            formData.append("file", file);
        }

        try {
            const response = await fetch("http://127.0.0.1:8000/uploadfile/", {
                method: "POST",
                // Set the FormData instance as the request body
                body: formData,
            });
            console.log(await response.json());
            filePicker.content = "";
        } catch (e) {
            console.error(e);
            filePicker.content = "";
        }
    }

    return (
        <Card mt="3" >
            <Flex pt="3" pb="3" align="center" justify="center">
                <input  type="file" id="soundFileInput" onChange={ (event) => submitFile(event.target) }/>
            </Flex>
        </Card>
    )
}