import React, { Fragment, useState } from 'react'

const Temperature = () => {
    const [number, setNumber] = useState(18)
    
    const aumentar = () => {
        setNumber(number + 1)
    }

    const reducir = () => {
        setNumber(number - 1)
    }

    return (
        <Fragment>
            <h2>Esta es la temperatura: {number}</h2>
            <p>{number > 21 ? 'Hace calor' : 'Hace frio'}</p>
            <button onClick={aumentar}>Aumentar</button>
            <button onClick={reducir}>Reducir</button>
        </Fragment>
    )
}

export default Temperature;