


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
        } catch (e) {
            console.error(e);
        }
    }

    return (
        <input type="file" id="soundFileInput" onChange={ (event) => submitFile(event.target) }/>
    )
}