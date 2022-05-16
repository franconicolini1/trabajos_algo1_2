import React, { useState } from "react"


const Form = () => {
    const [firstName, setFirstName] = useState('')
    const [SecondName, setSecondName] = useState('')

    const verificar = (e) => {
        if (!firstName.trim() || !SecondName.trim()) {
            e.preventDefault()
            return console.log('Ambos campos deben estar completos')
        }
    }

    return (
        <div className="container">
            <h1>Este es un super formulario</h1>
            <form className="form" onSubmit={verificar}>
                <input type="text" onChange={e => setFirstName(e.target.value)} placeholder="Ingrese su nombre"></input>
                <input type="text" onChange={e => setSecondName(e.target.value)} placeholder="Ingrese su apellido"></input>
                <input type="submit"></input>
            </form>
        </div>
    )
}

export default Form