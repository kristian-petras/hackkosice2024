import React, { useState } from "react";
import { Button, Card, Flex, Grid, Heading, Text, Box, Slider } from "@radix-ui/themes";
import {motion, AnimatePresence, delay} from "framer-motion";

const DurationSlider = ({ duration, onDurationChange }) => {
    const handleSliderChange = (value) => {
        onDurationChange(value);
    };

    return (
        <Flex direction="column" gap="2">
            <Text>Duration: {duration / 100}s</Text>
            <Slider
                min={1}
                max={100}
                step={1}
                defaultValue={[25]}
                value={[duration]}
                onValueChange={handleSliderChange}
            />
        </Flex>
    );
};


export default function NoteGrid() {
    const octaves = [0, 1, 2, 3, 4, 5, 6, 7, 8];
    const tones = [
        { note: 'C', color: 'gray' },
        { note: 'C#', color: 'gold' },
        { note: 'D', color: 'bronze' },
        { note: 'D#', color: 'brown' },
        { note: 'E', color: 'yellow' },
        { note: 'F', color: 'amber' },
        { note: 'F#', color: 'orange' },
        { note: 'G', color: 'tomato' },
        { note: 'G#', color: 'red' },
        { note: 'A', color: 'ruby' },
        { note: 'A#', color: 'crimson' },
        { note: 'B', color: 'pink' }
    ];

    const [duration, setDuration] = useState([25]);
    const handleDurationChange = (value) => {
        setDuration(value);
    };

    const [selectedTones, setSelectedTones] = useState([]);
    const handleButtonClick = (className, id, duration) => {
        if (duration === undefined) {
            duration = 25
        }
        setSelectedTones([...selectedTones, { className, id, duration }]);
        console.log('Added tone:', className, 'with id:', id, 'Duration:', duration[0] * 10);
    };

    const exportMelody = () => {
        const jsonString = JSON.stringify(selectedTones, null, 2);
        const blob = new Blob([jsonString], { type: 'application/json' });
        const url = window.URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = 'data.json'; // Filename
        document.body.appendChild(a);
        a.click();
        window.URL.revokeObjectURL(url);
        document.body.removeChild(a);
    };

    const handleDragOver = (event) => {
        event.preventDefault();
    };

    const handleDrop = (event) => {
        event.preventDefault();
        const file = event.dataTransfer.files[0];
        if (file) {
            const reader = new FileReader();
            reader.onload = (e) => {
                try {
                    const jsonData = JSON.parse(e.target.result);
                    setSelectedTones(jsonData);
                } catch (error) {
                    console.error('Error parsing JSON:', error);
                }
            };
            reader.readAsText(file);
        }
    };

    const emptyList = () => {
        setSelectedTones([]);
    }

    const removeFromList = (toneIndex) => {
        setSelectedTones(prevTones => {
            const updatedTones = [...prevTones];
            updatedTones.splice(toneIndex, 1);
            return updatedTones;
        });
    };

    const [isSubmitting, setIsSubmitting] = useState(false);

    const [showNotification, setShowNotification] = useState(false);
    const [notificationValue, setNotificationValue] = useState("Something wrong 😭")
    const [notificationColor, setNotificationColor] = useState({ backgroundColor: "color(display-p3 0.996 0.282 0.176 / 0.148)", border: "none"})

    const submitComposition = () => {
        setIsSubmitting(true); // Set loading state to true when submitting
        const url = 'http://127.0.0.1:8000/playComposition';
        const origin = 'http://127.0.0.1:3000'; // Client origin

        const pointsJson = selectedTones.map((tone) => {
            const [note, octa, color, _duration] = tone.className.split("-");
            return { "note": note, "octave": parseInt(octa), "duration": parseInt(_duration)};
        });

        const data = {
            points: pointsJson
        };


        fetch(url, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Origin': origin
            },
            body: JSON.stringify(data)
        })
            .then(response => {
                setIsSubmitting(false); // Reset loading state when response is received
                setShowNotification(true)
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }
                return response.json();
            })
            .then(data => {
                console.log('Response:', data);
                setShowNotification(true)
                setNotificationValue("Playing!😙")
                setNotificationColor({ backgroundColor: "color(display-p3 0.51 0.996 0.557 / 0.169);", border: "none"})
                setIsSubmitting(false);
            })
            .catch(error => {
                console.error('Error:', error);
                setShowNotification(true)
                setNotificationValue("Error!😭")
                setNotificationColor({ backgroundColor: "color(display-p3 0.996 0.282 0.176 / 0.148)", border: "none"})
                setIsSubmitting(false);
            });
    };

    return (
        <Flex direction="column" gapY="4">
            <Card mt="4">
                <Grid columns="9" gap="3" p="3" pb="5" pt="5">
                    {tones.map((tone, rowIndex) => (
                        octaves.map((item, colIndex) => {
                            const className = `${tone.note}-${item}-${tone.color}-${duration*10}`;
                            const id = `${tone.note}-${item}`;
                            return (
                                <Button key={colIndex} variant="soft" color={tone.color}
                                        onClick={() => handleButtonClick(className, id, duration)}>
                                    {tone.note + " - " + item}
                                </Button>
                            );
                        })
                    ))}
                </Grid>
            </Card>

            {showNotification && (
                <Card style={notificationColor}>
                    <Text>{notificationValue}</Text>
                </Card>
            )}

            <Flex direction="row" gapX="4">
                <Box width="25%">
                    <Card >
                        <Flex direction="column" gapY="4">
                            <Heading as="h2" size="6" mb="2">Control Panel</Heading>
                            <DurationSlider duration={duration} onDurationChange={handleDurationChange}/>
                            <Button>Pause</Button>
                            <Button onClick={() => emptyList()} disabled={selectedTones.length === 0}>Remove All</Button>

                            <Button disabled={selectedTones.length === 0}
                                    onClick={() => exportMelody()}>Export💾</Button>

                            <Button onClick={() => submitComposition()} disabled={selectedTones.length === 0 || isSubmitting}>
                                {isSubmitting ? 'Submitting...' : 'Submit ✅'}
                            </Button>
                        </Flex>
                    </Card>
                </Box>

                <Box width="75%"
                     onDragOver={handleDragOver}
                     onDrop={handleDrop}>
                    <Card>
                        <AnimatePresence>
                            {selectedTones.length > 0 && (
                                <>
                                    <Heading as="h2" size="6" mb="2">Timeline 🎵</Heading>
                                    <motion.div
                                        initial={{ opacity: 0, y: -20 }}
                                        animate={{ opacity: 1, y: 0 }}
                                        exit={{ opacity: 0, y: -20 }}
                                        transition={{ duration: 0.3 }}
                                    >
                                        <Flex direction="row" gap="3" wrap="wrap" pb="2" pt="3" >
                                            {selectedTones.map((tone, toneIndex) => {
                                                const [note, octa, color, _duration] = tone.className.split("-");
                                                const _width = 74 + parseInt(_duration ) / 10;
                                                return (
                                                    <Button key={toneIndex} variant="soft" color={color} onClick={() => removeFromList(toneIndex)} style={{ width: `${_width}px` }}>
                                                        {note + " - " + octa}
                                                    </Button>
                                                );
                                            })}
                                        </Flex>
                                    </motion.div>
                                </>
                            )}
                            {selectedTones.length === 0 && (
                                <motion.div
                                    initial={{ opacity: 0, y: -20 }}
                                    animate={{ opacity: 1, y: 0 }}
                                    exit={{ opacity: 0, y: -20 }}
                                    transition={{ duration: 0.3 }}
                                >
                                    <Heading mb="2" mt="2">Timeline is empty 😔, please add some tunes🤩🎵!</Heading>
                                </motion.div>
                            )}
                        </AnimatePresence>
                    </Card>
                </Box>
            </Flex>
        </Flex>
    )
}
